/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:18:57 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 13:39:12 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_args(t_cmd **cmd, t_ms *ms);

/** @brief expand_cmd_args - Browse and expand each argument of given cmd.
 * 
 * @param cmd The cmd whose arguments must be expanded.
 * @param ms The minishell structure.
 * 
 * @returns HOME var value or NULL.
 */
void	expand_cmd_args(t_cmd **cmd, t_ms *ms)
{
	int		i;
	char	*tmp;
	t_cmd	*cmd_to_expand;
	char	*sdup;

	cmd_to_expand = (*cmd);
	i = 0;
	if (!cmd_to_expand)
		return ;
	if (!cmd_to_expand->args)
		return ;
	while (cmd_to_expand->args[i])
	{
		tmp = str_expand(cmd_to_expand->args[i], ms);
		if (!tmp)
			return (perror("minishell"));
		sdup = ft_strdup(tmp);
		if (!sdup)
			return (free(tmp), perror("minishell"));
		free(cmd_to_expand->args[i]);
		cmd_to_expand->args[i] = sdup;
		free(tmp);
		i++;
	}
	return ;
}
