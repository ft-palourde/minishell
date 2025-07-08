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

void	new_branch(int is_left, t_tree *parent, t_tree *child);
int		fill_tree(t_tree *node, t_token *list);
int		build_tree(t_ms *ms);

/** new_branch
 * @is_left: a boolean to check if the new branch is created on the parent's left
 * @parent: the parent node
 * @child: the child node
 * 
 * sets the child at the right branch of the parent and the parent as the child's
 * parent
 *
 * Returns: void
 */
void	new_branch(int is_left, t_tree *parent, t_tree *child)
{
	if (is_left)
	{
		if (child->token->is_piped)
		{
			parent->left = child->parent;
			parent->left->parent = parent;
		}
		else
			parent->left = child;
	}
	else
	{
		parent->right = child;
		child->token->is_piped = 1;
	}
	child->parent = parent;
}

/** redir_branch
 * @node: the current node
 * @list: the current element of the token list
 * 
 * add the node on the bottom of the redir branch
 *
 * Returns: 1 if there is a redir to handle
 * or 0 on malloc error or non-redir
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
			return (perror("minishell"), 0);
		cursor->right = new;
		new->parent = cursor;
		return (1);
	}
	return (0);
}

/** fill_tree
 * @node: the first node of the tree
 * @list: the list of tokens to fill in the tree
 * 
 * fill the tree with all element of the list of tokens
 *
 * Returns: 1 on malloc error, 0 else
 */
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
			return (perror("minishell"), 1);
		while (redir_branch(node, list->next))
			list = list->next;
		if (prev_node->token->type != T_PIPE)
			new_branch(1, node, prev_node);
		else if (!prev_node->right)
			new_branch(0, prev_node, node);
		else
			new_branch(1, node, prev_node);
		if (list)
			list = list->next;
	}
	return (0);
}

/** build_tree
 * @ms: minishell data structure
 * 
 * initialise and build the binary tree containing the tokens to execute
 *
 * Returns: 1 on malloc error 0 else
 */
int	build_tree(t_ms *ms)
{
	ms->tree = get_new_node(ms->token);
	if (!ms->tree)
		return (perror("minishell"), 1);
	if (fill_tree(ms->tree, ms->token->next))
		free_tree(ms->tree);
	ms->tree = get_root(ms->tree);
	return (0);
}
