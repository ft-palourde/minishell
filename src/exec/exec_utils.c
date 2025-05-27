/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:29:27 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/27 13:16:41 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*add_fd(int fd, t_ms *ms)
{
	int	i;
	int	*pfd;

	pfd = ms->pfd;
	i = 0;
	if (!pfd)
	{
		pfd = ft_calloc(2, sizeof(int));
		if (!pfd)
			return (perror("malloc"), NULL);
		pfd[0] = fd;
		return (0);
	}
	while (pfd[i])
		i++;
	pfd = ft_realloc(pfd, (i + 2) * sizeof(int));
	if (!pfd)
		return (perror("malloc"), NULL);
	pfd[i] = fd;
	return (pfd);
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