/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:27:10 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/27 12:32:29 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_outfile(t_token *list, t_tree *node);
void	new_branch(int is_left, t_tree *parent, t_tree *child);
int		fill_tree(t_tree *node, t_token *list);
int		build_tree(t_ms *ms);

int	check_outfile(t_token *list, t_tree *node)
{
	t_tree	*new;

	if (!list || !list->next)
		return (1);
	if (list->next->type != T_REDIR_OUT && list->next->type != T_APPEND)
		return (1);
	new = get_new_node(list->next);
	new->parent = node;
	if (!new)
		return (perror("malloc"), 1);
	node->right = new;
	return (0);
}

void	new_branch(int is_left, t_tree *parent, t_tree *child)
{
	if (is_left)
		parent->left = child;
	else
		parent->right = child;
	child->parent = parent;
}

int	fill_tree(t_tree *node, t_token *list)
{
	t_tree		*prev_node;

	if (!check_outfile(list, node))
				list = list->next;
	if (list)
		list = list->next;
	while (list)
	{
		prev_node = node;
		node = get_new_node(list);
		if (!check_outfile(list, node))
				list = list->next;
		if (prev_node->token->type != T_PIPE)
			new_branch(1, node, prev_node);
		else if (!prev_node->right)
		{
			new_branch(0, prev_node, node);
			node = prev_node;
		}
		else
			new_branch(1, node, prev_node);
		if (list)
			list = list->next;
	}
	return (0);
}

//verifier les malloc + le cas du node 1.
int	build_tree(t_ms *ms)
{
	ms->tree = get_new_node(ms->token);
	if (!ms->tree)
		return (perror("malloc"), 1);
	if (fill_tree(ms->tree, ms->token))
		free_tree(ms->tree);
	ms->tree = get_root(ms->tree);
	return (0);
}
