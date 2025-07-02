/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:29:27 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:25:33 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** is_redir - check the token type
 * @type: a t_token_type value
 * 
 * checks if the token type is T_REDIR_IN / T_REDIR_OUT / T_APPEND
 *
 * Returns: 1 if yes, 0 else
 */
int	is_redir(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_APPEND)
		return (1);
	return (0);
}

/** add_pfd - add one pfd to ms->pfd array
 * @pfd: the pfd to add
 * @ms: minishell struct
 * 
 * realloc the array ms->pfd and add pfd at the end of it
 *
 * Returns: 1 on malloc failed, 0 else
 */
int	add_pfd(int *pfd, t_ms *ms)
{
	int	i;
	int	**new_pfd;

	i = 0;
	if (!ms->pfd)
	{
		ms->pfd = ft_calloc(2, sizeof(int *));
		if (!ms->pfd)
			return (perror("malloc"), close(pfd[0]), close(pfd[1]), 1);
		ms->pfd[0] = pfd;
		return (0);
	}
	while (ms->pfd[i])
		i++;
	new_pfd = ft_calloc(i + 2, sizeof(int *));
	if (!new_pfd)
		return (perror("malloc"), close(pfd[0]), close(pfd[1]), 1);
	new_pfd[i] = pfd;
	while (--i >= 0)
		new_pfd[i] = ms->pfd[i];
	free(ms->pfd);
	ms->pfd = new_pfd;
	return (0);
}

/** add_fd - add one fd to ms->fd array
 * @fd: the fd to add
 * @ms: minishell struct
 * 
 * realloc the array ms->fd and add fd at the end of it
 *
 * Returns: 1 on malloc failed, 0 else
 */
int	add_fd(int fd, t_ms *ms)
{
	int	i;
	int	*new_fd;

	i = 0;
	if (!ms->fd)
	{
		ms->fd = ft_calloc(2, sizeof(int));
		if (!ms->fd)
			return (perror("malloc"), 1);
		ms->fd[0] = fd;
		return (0);
	}
	while (ms->fd[i])
		i++;
	new_fd = ft_calloc(i + 2, sizeof(int));
	if (!new_fd)
		return (perror("malloc"), 1);
	new_fd[i] = fd;
	while (--i >= 0)
		new_fd[i] = ms->fd[i];
	free(ms->fd);
	ms->fd = new_fd;
	return (0);
}

/** close_fds - close all fds in ms->fd
 * @ms: minishell struct
 * 
 * close all fds stored in ms->fd with the add_fd function
 *
 * Returns: void
 */
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

/** is_absolute - path checker
 * @str: path
 * 
 * checks if the path contains a '/' char
 *
 * Returns: 1 is yes, 0 else
 */
int	is_absolute(char *str)
{
	if (str && ft_strchr(str, '/'))
		return (1);
	return (0);
}
