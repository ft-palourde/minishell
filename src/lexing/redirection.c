/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:31:01 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/14 17:55:14 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_token_type type, t_rd *rd);

void	free_redir(t_token_type type, t_rd *rd)
{
	if (!rd)
		return ;
	if (is_redir(type) && rd->file)
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
