/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:10:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 15:28:40 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_quote(char *input, t_token **tokens);
int		is_quote(char c);
int		get_quoted_len(char quote, char *str);

/** is_quote - Read a char and return if it is a quote char.
 * @c: The char read compared to simple and double quote.
 *
 * Returns: An int as boolean, 1 true, 0 false.
 */
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/** handle_quote - .
 * @input: .
 * @tokens:
 * 
 * Returns: The len (int) of .
 */
int	handle_quote(char *input, t_token **tokens)
{
	t_token			*new_token;
	int				len;
	char			quote;

	len = 1;
	quote = *input;
	len = get_quoted_len(quote, input);
	len += extract_word_len(input + len);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->type = T_WORD;
	new_token->str = ft_strndup(input, len);
	if (!new_token->str)
		free_token(new_token);
	new_token->next = NULL;
	ft_memset(&new_token->data, 0, sizeof(new_token->data));
	add_to_tokens(new_token, tokens);
	return (len);
}

/** get_quoted_len - Get the len of the str between 2 same and unescaped quotes.
 * @quote: quote set as limiter.
 * @input: str to read until limiter.
 * 
 * Returns: The len (int) of the part between same quote type.
 */
int	get_quoted_len(char quote, char *input)
{
	int	quoted_len;

	quoted_len = 1;
	while (input[quoted_len])
	{
		if (input[quoted_len] == quote)
			break ;
		quoted_len++;
	}
	if (input[quoted_len] == quote)
		quoted_len++;
	return (quoted_len);
}
