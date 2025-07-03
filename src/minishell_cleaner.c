/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:29:28 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/03 19:17:03 by rcochran         ###   ########.fr       */
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

void	clean_fds(int *fd)
{
	int	i;

	i = 0;
	if (!fd)
		return ;
	if (!fd[i])
		return ;
	while (fd[i])
	{
		if (fd[i])
			close(fd[i]);
		i++;
	}
}

void	clean_pfds(int	**pfd)
{
	int	i;

	i = 0;
	if (!pfd)
		return ;
	if (!pfd[i])
		return ;
	while (pfd[i])
	{
		if (pfd[i])
			free(pfd[i]);
		i++;
	}
	free(pfd);
}

void	ms_cleaner(t_ms *ms)
{
	if (ms->file_in != STDIN_FILENO)
		close(ms->file_in);
	if (ms->file_out != STDOUT_FILENO)
		close(ms->file_out);
	if (ms->fd)
	{
		clean_fds(ms->fd);
		free(ms->fd);
	}
	if (ms->pfd)
		clean_pfds(ms->pfd);
	if (ms->pid)
		free(ms->pid);
	if (ms->token)
		free_tokens(ms->token);
	if (ms->tree)
		free_tree(ms->tree);
}

void	ms_full_clean(t_ms *ms)
{
	if (!ms)
		return ;
	if (ms->exit == -1)
		ms_cleaner(ms);
	free(ms->prompt);
	free(ms->term);
	reverse_cascade_free(ms->env, split_len(ms->env));
	close(ms->ms_stdin);
	close(ms->ms_stdout);
	clear_history();
	free(ms);
}
