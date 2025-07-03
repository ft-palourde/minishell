/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:23:44 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 17:21:50 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** dup_handler - do the needed redirections with dup2
 * @token: the t_token currently in use by the exec_tree
 * @ms: the minishell struct
 * 
 * if there is any redirection or pipe to do, this function
 * will handle it with the right priority (redir before pipe)
 * You should call for reset_dup after this function to reset it
 * after the command execution.
 *
 * Returns: void
 */
void	dup_handler(t_token *token, t_ms *ms)
{
	(void)token;
	(void)ms;
	if (ms->file_in != STDIN_FILENO)
		dup2(ms->file_in, STDIN_FILENO);
	else if (token->in_fd != STDIN_FILENO)
		dup2(token->in_fd, STDIN_FILENO);
	if (ms->file_out != STDOUT_FILENO)
		dup2(ms->file_out, STDOUT_FILENO);
	else if (token->out_fd != STDOUT_FILENO)
		dup2(token->out_fd, STDOUT_FILENO);
}

/** reset_dup - reset STDIN and STDOUT after a dup
 * @in_fd: token->in_fd
 * @out_fd: token->out_fd
 * @ms: the minishell struct
 * 
 * if called after the use of dup to redirect STDIN or STDOUT
 * reset_dup sets them back to their original value
 *
 * Returns: void
 */
void	reset_dup(int in_fd, int out_fd, t_ms *ms)
{
	if (ms->file_in == STDIN_FILENO && ms->file_out == STDOUT_FILENO \
		&& in_fd == STDIN_FILENO && out_fd == STDOUT_FILENO)
		return ;
	reset_std_dup(ms);
	if (ms->file_in != STDIN_FILENO)
		close (ms->file_in);
	if (ms->file_out != STDOUT_FILENO)
		close (ms->file_out);
	if (in_fd != STDIN_FILENO)
		close (in_fd);
	if (out_fd != STDOUT_FILENO)
		close (out_fd);
}

/** reset_ms_files
 * @ms: the minishell struct
 * 
 * resets the value of ms->file_in and ms->file_out 
 * to basic STDIN and STDOUT values
 *
 * Returns: void
 */
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

/** add_pid - add one pid to the ms->pid array
 * @pid: the new pid to add
 * @ms: the minishell struct
 * 
 * realloc the ms->pid array with the new pid at the end of it
 *
 * Returns: 1 on malloc error, 0 else
 */
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

void	reset_std_dup(t_ms *ms)
{
	dup2(ms->ms_stdin, STDIN_FILENO);
	dup2(ms->ms_stdout, STDOUT_FILENO);
}
