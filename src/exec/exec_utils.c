/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:29:27 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/13 09:33:39 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_APPEND)
		return (1);
	return (0);
}

int	add_pfd(int *pfd, t_ms *ms)
{
	int	i;
	int	**new_pfd;

	i = 0;
	if (!ms->pfd)
	{
		ms->pfd = ft_calloc(2, sizeof(int *));
		if (!ms->pfd)
			return (perror("malloc"), 0);
		ms->pfd[0] = pfd;
		return (0);
	}
	while (ms->pfd[i])
		i++;
	new_pfd = ft_calloc(i + 2, sizeof(int *));
	if (!new_pfd)
		return (perror("malloc"), 0);
	new_pfd[i] = pfd;
	while (--i >= 0)
		new_pfd[i] = ms->pfd[i];
	free(ms->pfd);
	ms->pfd = new_pfd;
	return (0);
}

int	add_fd(int fd, t_ms *ms)
{
	int	i;
	int	*new_fd;

	i = 0;
	if (!ms->fd)
	{
		ms->fd = ft_calloc(2, sizeof(int));
		if (!ms->fd)
			return (perror("malloc"), 0);
		ms->fd[0] = fd;
		return (0);
	}
	while (ms->fd[i])
		i++;
	new_fd = ft_calloc(i + 2, sizeof(int));
	if (!new_fd)
		return (perror("malloc"), 0);
	new_fd[i] = fd;
	while (--i >= 0)
		new_fd[i] = ms->fd[i];
	free(ms->fd);
	ms->fd = new_fd;
	return (0);
}

/* int	add_fd(int fd, t_ms *ms)
{
	int	i;

	i = 0;
	if (!ms->fd)
	{
		ms->fd = ft_calloc(2, sizeof(int));
		if (!ms->fd)
			return (perror("malloc"), 0);
		ms->fd[0] = fd;
		return (0);
	}
	while (ms->fd[i])
		i++;
	ms->fd = ft_realloc(ms->fd, (i + 2) * sizeof(int));
	if (!ms->fd)
		return (perror("malloc"), 0);
	ms->fd[i] = fd;
	ms->fd[i + 1] = 0;
	return (0);
} */

void	close_fds(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->fd && ms->fd[i])
	{
		close(ms->fd[i]);
		i++;
	}
	if (ms->file_in != STDIN_FILENO)
		close(ms->file_in);
	if (ms->file_out != STDOUT_FILENO)
		close(ms->file_out);
	close(ms->ms_stdin);
	close(ms->ms_stdout);
}

int	is_absolute(char *str)
{
	(void) str;
	return (0);
}
