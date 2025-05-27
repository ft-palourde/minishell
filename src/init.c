/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:35:30 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/27 12:36:49 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*init_ms_struct(char **env)
{
	t_ms	*new;

	new = ft_calloc(1, sizeof(t_ms));
	if (!new)
		return (NULL);
	new->env = set_env(env, 1);
	new->ms_stdin = dup(STDIN_FILENO);
	new->ms_stdout = dup(STDOUT_FILENO);
	return (new);
}