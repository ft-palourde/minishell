/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:29:27 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/23 12:42:57 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*add_fd(int fd, int *ms_fd)
{
	int	i;

	i = 0;
	if (!ms_fd)
	{
		ms_fd = ft_calloc(2, sizeof(int));
		if (!ms_fd)
			return (perror("malloc"), NULL);
		ms_fd[0] = fd;
		return (0);
	}
	while (ms_fd[i])
		i++;
	i++;
	ms_fd = ft_realloc(ms_fd, i * sizeof(int));
	if (!ms_fd)
		return (perror("malloc"), NULL);
	ms_fd[i] = fd;
	return (ms_fd);
}

void	close_fds(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->pfd && ms->pfd[i])
	{
		close(ms->pfd[i]);
		i++;
	}
	if (ms->file_in)
		close(ms->file_in);
	if (ms->file_out)
		close(ms->file_out);
}

int	is_absolute(char *str)
{
	(void) str;
	return (0);
}