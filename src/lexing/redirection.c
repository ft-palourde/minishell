/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:31:01 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:39:47 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_rd *rd);

/**
 * @brief Free a redirection structure.
 *
 * @param rd Pointer to the redirection structure to free.
 */
void	free_redir(t_rd *rd)
{
	if (!rd)
		return ;
	if (rd->file)
	{
		free(rd->file->filename);
		rd->file->fd = 0;
		free(rd->file);
	}
	else if (rd->heredoc)
	{
		free(rd->heredoc->lim);
		free(rd->heredoc);
	}
	free(rd);
}
