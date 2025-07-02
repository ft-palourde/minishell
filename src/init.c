/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:35:30 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/22 12:42:15 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	*init_ms_struct(char **env)
{
	t_ms	*new;

	new = ft_calloc(1, sizeof(t_ms));
	if (!new)
		return (NULL);
	new->file_in = STDIN_FILENO;
	new->file_out = STDOUT_FILENO;
	new->env = set_env(env);
	new->ms_stdin = dup(STDIN_FILENO);
	new->ms_stdout = dup(STDOUT_FILENO);
	new->term = malloc(sizeof(t_termios));
	new->exit = -1;
	new->retval = 0;
	if (!new->term)
		return (NULL);
	new->prompt = get_prompt(env);
	if (!new->prompt)
		return (NULL);
	return (new);
}
