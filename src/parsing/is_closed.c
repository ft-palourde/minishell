/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 12:11:55 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quote(t_token *token);
int	check_quote_error(char *str, char c);
int	is_closed(char *str, char c);
int	is_quoted(char *str, char c);

/*
checks if the quote, double quote or parenthesis has a closing occurence
returns the number of char read if found, 0 otherwise
*/
int	is_closed(char *str, char c)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	i = 1;
	in_single_quote = 0;
	in_double_quote = 0;
	if (c == '(')
		c = ')';
	while (str[i])
	{
		if (str[i] == '\'' && !is_escaped(str, i) && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !is_escaped(str, i) && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (!in_single_quote && !in_double_quote && str[i] == c
			&& !is_escaped(str, i))
			return (i);
		i++;
	}
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
	int		i;
	int		nb_quote;
	int		is_quoted;
	char	other_quote;

	is_quoted = 0;
	i = 0;
	nb_quote = 0;
	if (c == '\'')
		other_quote = '"';
	else
		other_quote = '\'';
	while (str[i])
	{
		nb_quote += (str[i] == c && !is_escaped(str, i));
		i++;
	}
	return (nb_quote % 2);
}

