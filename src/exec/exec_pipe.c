/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:53 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/23 12:07:03 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_tree *node, t_ms *ms)
{
	int	*pfd;

	pfd = ft_calloc(2, sizeof(int));
	(void) ms;
	if (!pfd || pipe(pfd) == -1)
		return (-1);
	if (node->parent && node->parent->token->type == T_PIPE)
	{
		node->right->token->out_fd = node->token->out_fd;
	}
	node->left->token->out_fd = pfd[1];
	node->right->token->in_fd = pfd[0];
	add_fd(pfd[0], ms->pfd);
	add_fd(pfd[1], ms->pfd);
	return (0);
}
