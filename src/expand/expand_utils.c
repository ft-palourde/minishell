/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:14:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 12:09:13 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_chunk(char *str);
int		check_quote_type(char c);
void	add_var_to_new(char **new, char *str, t_ms *ms);
int		expand_is_closed(char *str, char c);

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
		return (perror("malloc"), NULL);
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

/*
checks if the quote, double quote or parenthesis has a closing occurence
returns the number of char read if found, 0 otherwise
*/
int	expand_is_closed(char *str, char c)
{
	int		i;

	i = 1;
	if (c == '(')
		c = ')';
	while (str[i] != c && str[i])
		i++;
	if (str[i] && !is_escaped(str, i))
		return (i);
	return (0);
}
