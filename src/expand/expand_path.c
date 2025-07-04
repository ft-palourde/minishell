/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:33:45 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/04 18:57:16 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_path(char *str, t_ms *ms);

char	*expand_path(char *str, t_ms *ms)
{
	char	*home;
	char	*expanded_path;

	if (!str || str[0] != '~')
		return (NULL);
	home = var_name_to_value("HOME", ms);
	if (!home)
		return (NULL);
	if (str[1] == '\0' || str[1] == '/')
		expanded_path = ft_strdup(home);
	// else if (str[1] == '/')
		// expanded_path = ft_strjoin(home, str + 1);
	else
	{
		expanded_path = ft_strdup("~");
		if (!expanded_path)
			return (NULL);
		// free(home);
		// return (NULL);
		// return ("~");
	}
	free(home);
	return (expanded_path);
}
