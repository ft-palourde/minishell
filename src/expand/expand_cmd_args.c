/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:18:57 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/15 11:55:40 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_args(t_cmd *cmd, t_ms *ms);
void	clear_empty_strings(char **new_arg);

/**
 * @brief Expand all arguments of a command.
 *
 * Applies variable expansion to each argument in the command.
 *
 * @param cmd Pointer to the command to expand.
 * @param ms The minishell structure.
 */
void	expand_cmd_args(t_cmd *cmd, t_ms *ms)
{
	int		i;
	char	*expanded;

	i = 0;
	if (!cmd || !cmd->args)
		return ;
	while (cmd->args[i])
	{
		expanded = str_expand(cmd->args[i], ms);
		if (!expanded)
			return (perror("minishell"));
		cmd->args[i] = expanded;
		i++;
	}
	clear_empty_strings(cmd->args);
	return ;
}

void	clear_empty_strings(char **new_arg)
{
	int	i;

	while (!new_arg[0][0])
	{
		i = 0;
		free(new_arg[0]);
		new_arg[0] = 0;
		while (new_arg[i + 1])
		{
			new_arg[i] = new_arg[i + 1];
			i++;
		}
	}
}
