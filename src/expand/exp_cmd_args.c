/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:18:57 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/13 11:19:16 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_args(t_cmd *cmd, char **env);

void	expand_cmd_args(t_cmd *cmd, char **env)
{
	int		i;
	char	**expanded_args;
	char	*tmp;

	i = 1;
	while (cmd->args[i])
	{
		tmp = str_expand(cmd->args[i], env);
		free(cmd->args[i]);
		cmd->args[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	return ;
}
