/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:20:39 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/01 15:39:26 by rcochran         ###   ########.fr       */
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
	ms->file_in = pfd[0];
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
	char	*buff;
	int		cursor;

	cursor = 1;
	node->token->in_fd = ms->file_in;
	node->token->out_fd = ms->file_out;
	if (pipe_heredoc(node, ms))
		return (1);
	buff = ft_calloc(3, sizeof(char));
	if (!buff)
		return (perror("malloc"), 1);
	while (cursor)
	{
		cursor = read(node->token->data->rd->heredoc->fd[0], buff, 2);
		if (cursor == -1)
		{
			ft_putendl_fd("read : error occured.", 2);
			break ;
		}
		if (cursor)
			ft_putstr_fd(buff, node->token->out_fd);
	}
	free(buff);
	close(node->token->out_fd);
	return (0);
}
