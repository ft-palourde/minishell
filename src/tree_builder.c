/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:27:10 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/25 13:38:22 by tcoeffet         ###   ########.fr       */
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
/* 
si le node est une redir : tant que j'ai des redirs je les add a droite
*/

int	redir_branch(t_tree *node, t_token *list)
{
	t_tree	*new;
	t_tree	*cursor;

	cursor = node;
	new = 0;
	if (!list)
		return (0);
	while (cursor && cursor->right && (is_redir(cursor->right->token->type) \
		|| cursor->right->token->type == T_HEREDOC))
		cursor = cursor->right;
	if (is_redir(list->type) || list->type == T_HEREDOC)
	{
		new = get_new_node(list);
		if (!new)
			return (perror("malloc"), 0);
		cursor->right = new;
		new->parent = cursor;
		return (1);
	}
	return (0);
}

int	fill_tree(t_tree *node, t_token *list)
{
	t_tree		*prev_node;

	while (redir_branch(node, list))
		list = list->next;
	while (list)
	{
		prev_node = node;
		node = get_new_node(list);
		if (!node)
			return (perror("malloc"), 1);
		while (redir_branch(node, list->next))
			list = list->next;
		if (prev_node->token->type != T_PIPE)
			new_branch(1, node, prev_node);
		else if (!prev_node->right)
		{
			new_branch(0, prev_node, node);
			//node = prev_node;
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
	if (fill_tree(ms->tree, ms->token->next))
		free_tree(ms->tree);
	ms->tree = get_root(ms->tree);
	return (0);
}
