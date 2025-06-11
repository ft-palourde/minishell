/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:28:07 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/09 17:39:15 by tcoeffet         ###   ########.fr       */
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

void	print_spaces(int i)
{
	int	j;

	j = 0;
	while (j < i * 2)
	{
		dprintf(2, " |");
		j++;
	}
}

void	debug_print_tree(t_tree *root, int i)
{
	if (!i)
		dprintf(2, "\n______________\n\n DEBUG \n\n\n");
	print_spaces(i);
	dprintf(2, "[%d]current node = %s", i, root->token->str);
	if (is_redir(root->token->type))
		dprintf(2, " %s", root->token->data->rd->file->filename);
	dprintf(2, "\n");
	if (root->left)
	{
		print_spaces(i);
		dprintf(2, "left = %s\n", root->left->token->str);
		debug_print_tree(root->left, i + 1);
	}
	else
	{
		print_spaces(i);
		dprintf(2, "left = [X]\n");
	}
	if (root->right)
	{
		print_spaces(i);
		dprintf(2, "right = %s\n", root->right->token->str);
		debug_print_tree(root->right, i + 1);
	}
	else
	{
		print_spaces(i);
		dprintf(2, "right = [X]\n");
	}
}
