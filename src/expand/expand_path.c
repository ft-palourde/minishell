/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:33:45 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 12:42:41 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_path(char *str, t_ms *ms, int exp);

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
