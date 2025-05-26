/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:27:10 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/15 18:34:47 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*get_new_node(t_token *token)
{
	t_tree	*new;

	new = ft_calloc (1, sizeof(t_tree));
	if (!new)
		return (0);
	new->token = token;
	new->left = 0;
	new->right = 0;
	return (new);
}

int	check_outfile(t_token *list, t_tree *node)
{
	t_tree	*new;

	if (list->next->type != T_REDIR_OUT)
		return (1);
	new = get_new_node(list->next);
	if (!new)
		return (perror("malloc"), 1);
	node->right = new;
	return (0);
}

int	fill_tree(t_tree **root, t_tree *node, t_token *list)
{
	t_tree		*prev_node;

	(void) root;
	while (list)
	{
		prev_node = node;
		node = get_new_node(list);
		if (is_redir(node->token->type))
		{
			
		}
		else
		{
		if (prev_node->token->type != T_PIPE)
			node->left = prev_node;
		else if (!prev_node->right)
		{
			if (!check_outfile(list, node))
				list = list->next;
			prev_node->right = node;
			node = prev_node;
		}
		else
			node->left = prev_node;
		if (list)
			list = list->next;
		}
	}
	return (0);
}

//verifier les malloc + le cas du node 1.
int	build_tree(t_ms *ms)
{
	ms->tree = get_new_node(ms->token);
	if (!ms->tree)
		return (perror("malloc"), 1);
	if (fill_tree(&ms->tree, ms->tree, ms->token->next))
		free_tree(ms->tree);
	return (0);
}
