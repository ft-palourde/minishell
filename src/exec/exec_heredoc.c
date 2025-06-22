/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:20:39 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 12:37:46 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_heredoc(t_tree *node, t_ms *ms)
{
	int	*pfd;

	pfd = ft_calloc(2, sizeof(int));
	if (!pfd || pipe(pfd) == -1)
		return (1);
	node->parent->token->in_fd = pfd[0];
	node->token->out_fd = pfd[1];
	if (add_fd(pfd[0], ms) || add_fd(pfd[1], ms) || add_pfd(pfd, ms))
		return (1);
	return (0);
}

int	exec_heredoc(t_tree *node, t_ms *ms)
{
	char	*line;

	node->token->in_fd = ms->file_in;
	node->token->out_fd = ms->file_out;
	if (node->parent && node->parent->token->type == T_CMD)
	{
		if (pipe_heredoc(node, ms))
			return (1);
	}
	else
		return (0);
	dup_handler(node->token, ms);
	line = get_next_line(node->token->data->rd->heredoc->fd[0]);
	if (!line)
		return (1);
	while (line)
	{
		ft_putstr_fd(line, node->token->out_fd);
		free(line);
		line = get_next_line(node->token->data->rd->heredoc->fd[0]);
	}
	reset_dup(node->token->in_fd, node->token->out_fd, ms);
	return (0);
}
