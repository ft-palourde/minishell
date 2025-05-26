/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/26 19:02:56 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quote(t_token *token);
int	check_quote_error(char *str, char c);
int	is_closed(char *str, char c);

/*
checks if the quote, double quote or parenthesis has a closing occurence
returns the number of char read if found, 0 otherwise
*/
int	is_closed(char *str, char c)
{
	int		i;

	i = 1;
	if (c == '(')
		c = ')';
	while (str[i] != c && str[i])
		i++;
	if (str[i] && is_escaped(str, i))
		return (i);
	return (0);
}

/* 
check for each node of type word if its str contains quote error
*/
int	unclosed_quote(t_token *token)
{
	t_token	*cursor;

	cursor = token;
	while (cursor)
	{
		if (token->type == T_WORD)
		{
			if (check_quote_error(cursor->str, '\'') != 0
				|| check_quote_error(cursor->str, '\"') != 0)
				return (1);
		}
		cursor = cursor->next;
	}
	return (0);
}

/* 
counts unescaped quotes of same type
*/
int	check_quote_error(char *str, char c)
{
	int	i;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (str[i])
	{
		nb_quote += (str[i] == c && !is_escaped(str, i));
		i++;
	}
	return (nb_quote % 2);
}
