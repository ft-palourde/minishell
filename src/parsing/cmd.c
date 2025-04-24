/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:30:46 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/24 10:38:54 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd);

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				i++;
			reverse_cascade_free(cmd->args, i);
		}
		free(cmd->is_builtin);
		free(cmd->path);
		free(cmd);
	}
}
