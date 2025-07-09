/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:30:46 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 16:18:07 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd);
t_cmd	*new_cmd(void);

/** @brief free_cmd - free a cmd, its args and path.
 * @param cmd the cmd to free
 * 
 * @returns Void.
 */
void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->path)
		free(cmd->path);
	free(cmd);
}

/** @brief new_cmd - Create a new t_cmd cmd.
 * 
 * Initialize cmd args and path to null, is_builtin to false.
 * 
 * @returns the new t_cmd created.
 */
t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->is_builtin = false;
	return (cmd);
}
