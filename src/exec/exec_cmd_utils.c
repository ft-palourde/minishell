/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:23:44 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 12:25:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
