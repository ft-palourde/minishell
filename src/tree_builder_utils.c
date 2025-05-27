/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:28:07 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/27 12:37:30 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*get_root(t_tree *node);
t_tree	*get_new_node(t_token *token);
void	debug_print_tree(t_tree *root, int i);

t_tree	*get_root(t_tree *node)
{
	while (node && node->parent)
		node = node->parent;
	return (node);
}

t_tree	*get_new_node(t_token *token)
{
	t_tree	*new;

	new = ft_calloc (1, sizeof(t_tree));
	if (!new)
		return (0);
	new->parent = NULL;
	new->token = token;
	new->left = 0;
	new->right = 0;
	return (new);
}

void	debug_print_tree(t_tree *root, int i)
{
	int	space;

	space = 0;
	if (!i)
		dprintf(2, "\n______________\n\n DEBUG \n\n\n");
	while (space < i * 2)
	{
		space++;
		dprintf(2, "- ");
	}
	dprintf(2, "[%d]current node = %s\n", i, root->token->str);
	if (root->left)
	{
		dprintf(2, "left = %s\n", root->left->token->str);
		debug_print_tree(root->left, i + 1);
	}
	if (root->left)
	{
		dprintf(2, "right = %s\n", root->right->token->str);
		debug_print_tree(root->right, i + 1);
	}
}
