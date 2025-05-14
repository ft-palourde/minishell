/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:28 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/14 11:50:13 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_tree *tree)
{
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free(tree);
}

void	clean_fds(int	**pfd)
{
	while (pfd)
	{
		free(*pfd);
		pfd++;
	}
}

void	minishell_cleaner(t_ms *ms)
{
	if (ms->env)
		reverse_cascade_free(ms->env, split_len(ms->env));
	if (ms->file_in)
		close(ms->file_in);
	if (ms->file_out)
		close(ms->file_out);
	if (ms->pfd)
		clean_fds(ms->pfd);
	if (ms->pid)
		free(ms->pid);
	if (ms->token)
		free_token(ms->token);
	if (ms->tree)
		free_tree(ms->tree);
	free(ms);
}
