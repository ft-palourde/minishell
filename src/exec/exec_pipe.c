/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:53 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/21 17:40:34 by tcoeffet         ###   ########.fr       */
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
	node->left->token->out_fd = pfd[1];
	node->right->token->in_fd = pfd[0];
	return (0);
}
