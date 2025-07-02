/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_builder_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:17:50 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/02 16:17:50 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//////////////// DEBUG ////////////////

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

void	print_right(t_tree *root, int i)
{
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

void	print_left(t_tree *root, int i)
{
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
}

void	debug_print_tree(t_tree *root, int i)
{
	if (!i)
		dprintf(2, "\n______________\n\n DEBUG \n\n\n");
	print_spaces(i);
	dprintf(2, "[%d]current node = %s", i, root->token->str);
	if (is_redir(root->token->type))
		dprintf(2, " %s", root->token->data->rd->file->filename);
	if (root->token->type == T_HEREDOC)
		dprintf(2, " %s", root->token->data->rd->heredoc->lim);
	dprintf(2, "\n");
	print_left(root, i);
	print_right(root, i);
}
