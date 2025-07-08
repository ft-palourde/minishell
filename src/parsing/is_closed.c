/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 12:46:58 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unclosed_quote(t_token *token);
int		check_quote_error(char *str, char c);
int		is_closed(char *str, char c);
void	unclosed_quote_loop(t_token *cursor,
			int *in_double_quote, int *in_single_quote);

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
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	cursor = token;
	while (cursor)
	{
		if (cursor->type == T_WORD)
		{
			i = 0;
			in_single_quote = 0;
			in_double_quote = 0;
			unclosed_quote_loop(cursor, &in_double_quote, &in_single_quote);
			if (in_single_quote || in_double_quote)
				return (1);
		}
		cursor = cursor->next;
	}
	return (0);
}

void	unclosed_quote_loop(t_token *cursor,
	int *in_double_quote, int *in_single_quote)
{
	int	i;

	i = 0;
	while (cursor->str[i])
	{
		if (cursor->str[i] == '\''
			&& !is_escaped(cursor->str, i) && !(*in_double_quote))
			(*in_single_quote) = !(*in_single_quote);
		else if (cursor->str[i] == '\"'
			&& !is_escaped(cursor->str, i) && !(*in_single_quote))
			(*in_double_quote) = !(*in_double_quote);
		i++;
	}
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
		if (str[i] == other_quote && !is_escaped(str, i))
			is_quoted = !is_quoted;
		if (!is_quoted && str[i] == c && !is_escaped(str, i))
			nb_quote++;
		i++;
	}
	return (nb_quote % 2);
}
