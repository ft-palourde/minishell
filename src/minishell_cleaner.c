/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:28 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/27 14:26:07 by tcoeffet         ###   ########.fr       */
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

void	clean_fds(int *fd)
{
	int	i;

	i = 0;
	if (!fd[i])
		return ;
	while (fd[i])
	{
		if (fd[i])
			close(fd[i]);
		i++;
	}
}

void	ms_cleaner(t_ms *ms)
{
	free(ms->pid);
	if (ms->file_in)
		close(ms->file_in);
	if (ms->file_out)
		close(ms->file_out);
	if (ms->fd)
	{
		clean_fds(ms->fd);
		free(ms->fd);
	}
	if (ms->pid)
		free(ms->pid);
	if (ms->token)
		free_tokens(ms->token);
	if (ms->tree)
		free_tree(ms->tree);
}

void	ms_full_clean(t_ms *ms, char *prompt)
{
	if (!ms->exit)
		ms_cleaner(ms);
	free(prompt);
	reverse_cascade_free(ms->env, split_len(ms->env));
	close(ms->ms_stdin);
	close(ms->ms_stdout);
	free(ms);
}
