/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 16:29:38 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unclosed_quote(t_token *token);
int		is_closed(char *str, char c);
void	unclosed_quote_loop(t_token *cursor,
			int *in_double_quote, int *in_single_quote);

/** @brief is_closed - Check if then where there is a closing occurence.
 * 
 * @param str the input to read until closing quote or null byte.
 * @param c the quote set as limiter.
 *  
 * @returns returns the number of char read if found, 0 otherwise
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

/** @brief unclosed_quote - check if the given string contains a quote error.
 * 
 * @param str the token->str of a word token.
 *  
 * @returns returns 1 if error, 0 otherwise.
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

/** @brief unclosed_quote_loop - check if the token string contains quote error.
 * 
 * @param cursor current token to check
 * @param in_double_quote double quote error boolean
 * @param in_single_quote single quote error boolean
 *  
 * Update the 2 given booleans in parent function.
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
