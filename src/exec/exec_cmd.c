/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:50 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/04 11:15:00 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** cmd_is_empty - check if the given cmd is empty 
 * @token: the t_token of T_CMD type
 * 
 * checks if the command contains any alphanumeric character
 *
 * Returns: 1 if the command is empty, 0 else
 */

int	cmd_is_empty(t_token *token)
{
	char	*cmd;
	int		i;

	i = 0;
	if (token && token->data && token->data->cmd
		&& token->data->cmd->args)
	{
		cmd = token->data->cmd->args[0];
		if (!cmd)
			return (1);
		while (cmd[i])
		{
			if (ft_isalnum(cmd[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

/** exec_builtin - call the right builtin to execute
 * @token: the t_token of T_CMD type
 * @ms: the minishell struct
 * 
 * checks the cmd name and if it is one of the builtins
 * and call it while handling the dup of STDIN or STDOUT if needed
 *
 * Returns: the command return value
 */

int	exec_builtin(t_token *token, t_ms *ms)
{
	t_built_in	builtin;
	int			retval;

	retval = -1;
	builtin = token->data->cmd->is_builtin;
	dup_handler(token, ms);
	if (builtin == B_CD)
		retval = bi_cd(ms->env, token->data->cmd->args[1]);
	if (builtin == B_ECHO)
		retval = bi_echo(token->data->cmd->args + 1);
	if (builtin == B_ENV)
		retval = bi_env(ms->env);
	if (builtin == B_EXIT)
		retval = bi_exit(ms, token->data->cmd->args);
	if (builtin == B_EXPORT)
		retval = bi_export(&ms->env, token->data->cmd->args + 1);
	if (builtin == B_PWD)
		retval = bi_pwd();
	if (builtin == B_UNSET)
		retval = bi_unset(ms->env, token->data->cmd->args + 1);
	reset_dup(token->in_fd, token->out_fd, ms);
	return (retval);
}

/** command_failed - handle the error if the cmd didnt exit
 * @token: the t_token of T_CMD type
 * @ms: the minishell struct
 * 
 * clear what needs to be closed or freed, then set the right
 * retval on the ms structure (127 if the command doesnt exist
 * or 0)
 * display an error message on STDERR if the command can not be executed
 *
 * Returns: void
 */
static void	command_failed(t_token *token, t_ms *ms)
{
	int	retval;

	if (access(token->data->cmd->path, X_OK))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(token->data->cmd->args[0], 2);
		if (is_absolute(token->data->cmd->args[0]))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		retval = 127;
	}
	else
		retval = 0;
	ms_cleaner(ms);
	reverse_cascade_free(ms->env, split_len(ms->env));
	free(ms->prompt);
	free(ms);
	exit(retval);
}

/** exec_child - executes the cmd in the child process
 * @token: the t_token of T_CMD type
 * @ms: the minishell struct
 * 
 * Dup the stdin and stdout if needed.
 * if the command is a builtin, call the right BI and clear before exit
 * else call the cmd with execve and call command failed if the cmd doesnt
 * exist or if the called file is not a program
 * 
 * Returns: void
 */
static void	exec_child(t_token *token, t_ms *ms)
{
	t_cmd	*cmd;
	int		is_bi;
	int		retval;

	reset_dlt_sig_behaviour();
	is_bi = is_builtin(token);
	cmd = token->data->cmd;
	dup_handler(token, ms);
	close_fds(ms);
	if (is_bi)
	{
		retval = exec_builtin(token, ms);
		ms_cleaner(ms);
		reverse_cascade_free(ms->env, split_len(ms->env));
		free(ms->prompt);
		free(ms->term);
		free(ms);
		exit(retval);
	}
	else
	{
		execve(cmd->path, cmd->args, ms->env);
		command_failed(token, ms);
	}
}

/** exec_cmd - execute the cmd node in the binary tree
 * @node: a t_tree node, must be a T_CMD type
 * @ms: the minishell struct
 * 
 * exec_cmd takes a node in parametter and fill the token
 * before executing the cmd, either it's a builtin or not.
 * If the cmd is a builtin and is not in or out a pipe 
 * it doesnt fork. In any other case it does fork.
 * 
 * Returns: void
 */
void	exec_cmd(t_tree *node, t_ms *ms)
{
	int	pid;

	if (init_cmd(node, ms) || ms->open_failed)
		return ;
	if (cmd_is_empty(node->token))
		return ;
	if (is_builtin(node->token) && \
		(!node->parent || node->parent->token->type != T_PIPE))
		exec_builtin(node->token, ms);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (!pid)
			exec_child(node->token, ms);
		else
		{
			if (add_pid(pid, ms))
				return ;
			reset_ms_files(ms);
			reset_dup(node->token->in_fd, node->token->out_fd, ms);
		}
		ms_signal_listener();
	}
}
