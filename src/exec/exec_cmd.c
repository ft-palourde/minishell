/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:50 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/15 21:00:38 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	si node.left ou node.right == redir : chopper le path de la redir
	creer les files si besoin. 
	
	expand les arguments de la cmd
	
	creer le fork
	
		faire les redirect si besoin (si redir ou si ms.fd_out ou ms.fd_in)
		
		close tous les pfd
		
		checker si builtin, si oui -> builtin si non -> execve

	parent
		penser a remettre les file_in et file_out a 0
*/

void	clear_cmd(t_token *token)
{
	free(token->data->cmd->path);
}

char	**get_paths(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_strncmp("PATH=", env[i], 5) && env[i])
		i++;
	while (env[i][j] != '=' && env[i][j])
		j++;
	if (env[i][j] != '=')
		return (ft_split("", '\0'));
	j++;
	return (ft_split(env[i] + j, ':'));
}

int	cmd_exists(char *cmd, char *path)
{
	char	*join;
	char	*join2;

	join = ft_strjoin(path, "/");
	if (!join)
		return (-1);
	join2 = ft_strjoin(join, cmd);
	if (!join2)
		return (free(join), -1);
	if (!access(join2, F_OK))
		if (!access(join2, X_OK))
			return (free(join), free(join2), 1);
	free(join);
	free(join2);
	return (0);
}

char	*add_paths(char *p1, char *p2)
{
	char	*new;
	char	*tmp;

	if (!p1 && !p2)
		return (NULL);
	if (!p1)
		return (p2);
	if (!p2)
		return (p1);
	new = ft_strjoin(p1, "/");
	if (!new)
		return (perror("malloc"), NULL);
	tmp = new;
	new = ft_strjoin(tmp, p2);
	free(tmp);
	return (new);
}

char	*get_cmd_path(t_cmd *cmd, char **paths)
{
	int		i;
	int		found;
	char	*not_found;

	i = 0;
	found = 0;
	cmd->path = cmd->args[0];
	if (!cmd->path)
		return (perror("malloc"), NULL);
	while (paths[i])
	{
		found = cmd_exists(cmd->path, paths[i]);
		if (found == -1)
			return (0);
		else if (found)
			return (add_paths(paths[i], cmd->path));
		i++;
	}
	not_found = ft_strdup(cmd->path);
	if (!not_found)
		perror("malloc");
	return (not_found);
}

int	init_cmd(t_tree *node, t_ms *ms)
{
	char	**paths;
	t_cmd	*cmd;

	cmd = node->token->data->cmd;
	expand_cmd_args(&cmd, ms);
	if (!is_builtin(node->token))
	{
		paths = get_paths(ms->env);
		if (!paths)
			return (1);
		cmd->path = get_cmd_path(node->token->data->cmd, paths);
		reverse_cascade_free(paths, split_len(paths));
		if (!cmd->path)
			return (perror("malloc"), 1);
	}
	if (ms->file_in != STDIN_FILENO)
		node->token->in_fd = ms->file_in;
	if (ms->file_out != STDOUT_FILENO)
		node->token->out_fd = ms->file_out;
	return (0);
}

void	dup_handler(t_token *token, t_ms *ms)
{
	if (ms->file_in != STDIN_FILENO)
		dup2(ms->file_in, STDIN_FILENO);
	else if (token->in_fd != STDIN_FILENO)
		dup2(token->in_fd, STDIN_FILENO);
	if (ms->file_out != STDOUT_FILENO)
		dup2(ms->file_out, STDOUT_FILENO);
	else if (token->out_fd != STDOUT_FILENO)
		dup2(token->out_fd, STDOUT_FILENO);
}

void	reset_dup(int in_fd, int out_fd, t_ms *ms)
{
	if (ms->file_in == STDIN_FILENO && ms->file_out == STDOUT_FILENO \
		&& in_fd == STDIN_FILENO && out_fd == STDOUT_FILENO)
		return ;
	dup2(ms->ms_stdin, STDIN_FILENO);
	dup2(ms->ms_stdout, STDOUT_FILENO);
	if (ms->file_in != STDIN_FILENO)
		close (ms->file_in);
	if (ms->file_out != STDOUT_FILENO)
		close (ms->file_out);
	if (in_fd != STDIN_FILENO)
		close (in_fd);
	if (out_fd != STDOUT_FILENO)
		close (out_fd);
}

void	exec_builtin(t_token *token, t_ms *ms)
{
	t_built_in	builtin;

	builtin = token->data->cmd->is_builtin;
	dup_handler(token, ms);
	if (builtin == B_CD)
		bi_cd(ms->env, token->data->cmd->args[1]);
	if (builtin == B_ECHO)
		bi_echo(token->data->cmd->args + 1);
	if (builtin == B_ENV)
		bi_env(ms->env);
	if (builtin == B_EXIT)
		bi_exit(ms);
	if (builtin == B_EXPORT)
		bi_export(&ms->env, token->data->cmd->args + 1);
	if (builtin == B_PWD)
		bi_pwd();
	if (builtin == B_UNSET)
		bi_unset(ms->env, token->data->cmd->args + 1);
	reset_dup(token->in_fd, token->out_fd, ms);
}

int	exec_child(t_token *token, t_ms *ms)
{
	t_cmd	*cmd;

	cmd = token->data->cmd;
	dup_handler(token, ms);
	close_fds(ms);
	execve(cmd->path, cmd->args, ms->env);
	ms->retval = 127;
	return (127);
}

int	add_pid(int pid, t_ms *ms)
{
	int	i;
	int	*new_pid;

	i = 0;
	if (!ms->pid)
	{
		ms->pid = ft_calloc(2, sizeof(int));
		if (!ms->pid)
			return (1);
		ms->pid[0] = pid;
		return (0);
	}
	while (ms->pid[i])
		i++;
	new_pid = ft_calloc(i + 2, sizeof(int));
	if (!new_pid)
		return (perror("malloc"), 1);
	new_pid[i] = pid;
	while (--i >= 0)
		new_pid[i] = ms->pid[i];
	free(ms->pid);
	ms->pid = new_pid;
	return (0);
}

void	command_failed(t_token *token, t_ms *ms)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(token->data->cmd->args[0], 2);
	if (is_absolute(token->data->cmd->args[0]))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	//clear_cmd(token);
	ms_cleaner(ms);
	reverse_cascade_free(ms->env, split_len(ms->env));
	free(ms->prompt);
	free(ms);
	exit(127);
}

void	reset_ms_files(t_ms *ms)
{
	if (ms->file_in != STDIN_FILENO)
	{
		close(ms->file_in);
		ms->file_in = STDIN_FILENO;
	}
	if (ms->file_out != STDOUT_FILENO)
	{
		close(ms->file_out);
		ms->file_out = STDOUT_FILENO;
	}
}

void	exec_cmd(t_tree *node, t_ms *ms)
{
	int	pid;

	if (init_cmd(node, ms) || ms->open_failed)
		return ;
	if (is_builtin(node->token))
		exec_builtin(node->token, ms);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (!pid)
		{
			ms->retval = exec_child(node->token, ms);
			command_failed(node->token, ms);
		}
		else
		{
			if (add_pid(pid, ms))
				return ;
			reset_ms_files(ms);
			reset_dup(node->token->in_fd, node->token->out_fd, ms);
		}
	}
}
