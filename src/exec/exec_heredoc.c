/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:20:39 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:06:09 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** pipe_heredoc - 
 * @node: current tree node carrying a T_HEREDOC type token
 * @ms: minishell struct
 * 
 * create the pipe needed to handle the heredoc and adds it to ms->pfd
 *
 * Returns: 1 on malloc or pipe failed, 0 else
 */
int	pipe_heredoc(t_tree *node, t_ms *ms)
{
	int	*pfd;

	pfd = ft_calloc(2, sizeof(int));
	if (!pfd || pipe(pfd) == -1)
		return (perror("pipe"), 1);
	node->parent->token->in_fd = pfd[0];
	node->token->out_fd = pfd[1];
	if (add_fd(pfd[0], ms) || add_fd(pfd[1], ms) || add_pfd(pfd, ms))
		return (perror("malloc"), 1);
	return (0);
}

/** exec_heredoc - execute a heredoc node
 * @node: current tree node carrying a T_HEREDOC type token
 * @ms: minishell struct
 * 
 * checks if the heredoc needs to be piped in something and dups
 * STDIN or STDOUT if needed before writing its content in the 
 * wanted fd.
 *
 * Returns: 1 on malloc or pipe failed, 0 else
 */
int	exec_heredoc(t_tree *node, t_ms *ms)
{
	char	*line;

	// signal_child();
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
	// signal_listener();
	return (0);
}
