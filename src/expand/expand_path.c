/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:33:45 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 17:43:57 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_path(char *str, t_ms *ms, int exp);

/** @brief expand_path - Get the HOME value in env.
 * 
 * @param str The string to expand.
 * @param ms The minishell structure.
 * @param exp boolean
 * 
 * If the boolean is 0 return NULL, else get the HOME var value.
 * 
 * @returns HOME var value or NULL.
 */
char	*expand_path(char *str, t_ms *ms, int exp)
{
	char	*home;
	char	*expanded_path;

	if (!str || str[0] != '~')
		return (NULL);
	if ((!str[1] || str[1] == '/') && exp == 1)
	{
		home = var_name_to_value("HOME", ms);
		if (!home)
			return (NULL);
		expanded_path = ft_strdup(home);
		if (!expanded_path)
			return (NULL);
		free(home);
		return (expanded_path);
	}
	else
	{
		expanded_path = ft_strdup("~");
		if (!expanded_path)
			return (NULL);
		return (expanded_path);
	}
}
