/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_init2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:42:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/15 09:43:02 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_inout(t_ms *ms, t_tree *node);

void	init_cmd_inout(t_ms *ms, t_tree *node)
{
	if (ms->file_in != STDIN_FILENO && ms->file_in != -1)
		node->token->in_fd = ms->file_in;
	if (ms->file_out != STDOUT_FILENO && ms->file_out != -1)
		node->token->out_fd = ms->file_out;
}
