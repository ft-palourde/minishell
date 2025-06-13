/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:33:45 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/13 15:33:45 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_path(char *str, t_ms *ms);

char	*expand_path(char *str, t_ms *ms)
{
	char	*expanded_path;

	expanded_path = NULL;
	if (*str != '~')
		return (free(expanded_path), NULL);
	expanded_path = var_name_to_value("HOME", ms);
	return (expanded_path);
}
