/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:14:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 18:10:12 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *var);
int		check_quote_type(char c);

/** @brief get_var_value - Get the value of a var in the env.
 * @param var The string containing the variable name and its value.
 * 
 *
 * @returns the variable value found after the = sign or NULL if error.
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

/** @brief check_quote_type - check if it is a single, double or no quote.
 * @param c The char to read.
 * 
 * @returns 1 if simple quote, 2 if double quote, 0 otherwise.
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
