/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:14:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 19:12:08 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_chunk(char *str);
int		check_quote_type(char c);

/* 
return the var part after "=" sign
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
