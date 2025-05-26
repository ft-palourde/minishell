/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:28 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/23 12:18:10 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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
	int	i;

	i = 0;
	if (!*pfd[i])
		return ;
	while (pfd[i])
	{
		if (*pfd[i])
			close(*pfd[i]);
		i++;
	}
}

void	ms_cleaner(t_ms *ms)
{
	if (ms->file_in)
		close(ms->file_in);
	if (ms->file_out)
		close(ms->file_out);
	if (ms->pfd)
	{
		clean_fds(&ms->pfd);
		free(ms->pfd);
	}
	if (ms->token)
		free_tokens(ms->token);
	if (ms->tree)
		free_tree(ms->tree);
}
