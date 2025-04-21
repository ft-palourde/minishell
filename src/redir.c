/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:31:01 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/21 17:59:42 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *rd);

void	free_redir(t_redir *rd)
{
	if (rd)
	{
		free(rd->is_append);
		free(rd->is_truncate);
		free(rd);
	}
}
