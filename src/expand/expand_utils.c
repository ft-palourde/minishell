/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:14:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 21:50:22 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *var);
int		check_quote_type(char c);

/**
 * @brief Extract the value from an environment variable string.
 *
 * @param var Environment variable string (format: VAR=value).
 * @return A newly allocated string containing the value, or NULL on error.
 */
char	*get_var_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] != '=')
		i++;
	value = ft_strdup(var + i + 1);
	if (!value)
		return (perror("minishell"), NULL);
	return (value);
}

/**
 * @brief Determine the type of a quote character.
 *
 * @param c Character to analyze.
 * @return 1 for single quote ('), 2 for double quote ("), 0 for others.
 */
int	check_quote_type(char c)
{
	if (!c)
		return (0);
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}
