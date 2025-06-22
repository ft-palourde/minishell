/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:50 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 12:32:11 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		retval = bi_exit(ms);
	if (builtin == B_EXPORT)
		retval = bi_export(&ms->env, token->data->cmd->args + 1);
	if (builtin == B_PWD)
		retval = bi_pwd();
	if (builtin == B_UNSET)
		retval = bi_unset(ms->env, token->data->cmd->args + 1);
	reset_dup(token->in_fd, token->out_fd, ms);
	return (retval);
}

void	command_failed(t_token *token, t_ms *ms)
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

int	exec_child(t_token *token, t_ms *ms)
{
	t_cmd	*cmd;
	int		is_bi;
	int		retval;

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
		ms->retval = 127;
		command_failed(token, ms);
	}
	return (ms->retval);
}

void	exec_cmd(t_tree *node, t_ms *ms)
{
	int	pid;

	if (init_cmd(node, ms) || ms->open_failed)
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
			ms->retval = exec_child(node->token, ms);
		else
		{
			if (add_pid(pid, ms))
				return ;
			reset_ms_files(ms);
			reset_dup(node->token->in_fd, node->token->out_fd, ms);
		}
	}
}
