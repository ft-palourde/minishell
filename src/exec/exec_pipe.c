/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:53 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:08:22 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** exec_pipe - execute a pipe node
 * @node: current tree node carrying a T_PIPE type token
 * @ms: minishell struct
 * 
 * create a pipe, add it's fds to the needed tokens and then to the ms struct
 *
 * Returns: 1 on pipe failed, 0 else
 */
int	exec_pipe(t_tree *node, t_ms *ms)
{
	int	*pfd;

	pfd = ft_calloc(2, sizeof(int));
	if (!pfd || pipe(pfd) == -1)
		return (perror("minishell"), 1);
	if (add_pfd(pfd, ms) || add_fd(pfd[0], ms) || add_fd(pfd[1], ms))
		return (close(pfd[0]), close(pfd[1]), free(pfd), 1);
	if (node->parent && node->parent->token->type == T_PIPE)
		node->right->token->out_fd = node->token->out_fd;
	if (node->left->token->type == T_CMD)
		node->left->token->out_fd = pfd[1];
	else
		close(pfd[1]);
	if (node->right->token->type == T_CMD)
		node->right->token->in_fd = pfd[0];
	else
		close(pfd[0]);
	return (0);
}
