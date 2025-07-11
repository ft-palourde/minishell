/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 23:04:48 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unclosed_quote(t_token *token);
int		is_closed(char *str, char c);
void	unclosed_quote_loop(t_token *cursor,
			int *in_double_quote, int *in_single_quote);

/**
 * @brief Check if a closing character exists, considering quotes.
 * 
 * @param str String to parse.
 * @param c Character to check for closure.
 * 
 * @return Number of characters read to find the closing character,
 *  or 0 if not closed.
 */
int	is_closed(char *str, char c)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	i = 1;
	in_single_quote = (*str == '\'');
	in_double_quote = (*str == '"');
	while (str[i] && (str[i] != c))
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (str[i] == c && (*str == '\''))
		in_single_quote = 0;
	else if (str[i] == c && (*str == '\"'))
		in_double_quote = 0;
	if (!in_single_quote && !in_double_quote && str[i] == c)
		return (i);
	return (0);
}

/**
 * @brief Check if a token list contains unclosed quotes.
 * 
 * @param token Head of the token list.
 * 
 * @return 1 if unclosed quotes are found, 0 otherwise.
 */
int	unclosed_quote(t_token *token)
{
	t_token	*cursor;
	int		in_single_quote;
	int		in_double_quote;

	cursor = token;
	while (cursor)
	{
		if (cursor->type == T_WORD)
		{
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

/**
 * @brief Helper function to detect unclosed quotes inside a token string.
 * 
 * @param cursor Current token being analyzed.
 * @param in_double_quote Pointer to double quote flag.
 * @param in_single_quote Pointer to single quote flag.
 * 
 * This function updates the quote flags according to the content of the string.
 */
void	unclosed_quote_loop(t_token *cursor,
	int *in_double_quote, int *in_single_quote)
{
	int	i;

	i = 0;
	while (cursor->str[i])
	{
		if (cursor->str[i] == '\''
			&& !(*in_double_quote))
			(*in_single_quote) = !(*in_single_quote);
		else if (cursor->str[i] == '\"'
			&& !(*in_single_quote))
			(*in_double_quote) = !(*in_double_quote);
		i++;
	}
}
