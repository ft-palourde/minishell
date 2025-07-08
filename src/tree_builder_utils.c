/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:28:07 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/25 14:34:52 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*get_root(t_tree *node);
t_tree	*get_new_node(t_token *token);

/** get_root
 * @node: any node of the tree
 * 
 * get the root node of the current tree
 *
 * Returns: root node of the current tree
 */
t_tree	*get_root(t_tree *node)
{
	while (node && node->parent)
		node = node->parent;
	return (node);
}

/** get_new_node
 * @token: the token to add as data of the node
 * 
 * create a new node for the tree and put the token given
 * in argument in it.
 *
 * Returns: the new node or NULL on malloc fail
 */
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
