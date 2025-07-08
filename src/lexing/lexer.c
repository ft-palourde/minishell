/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:26:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 15:32:02 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input);
t_token	*fill_tokens(char *input, int i, t_token *tokens);
int		extract_word_len(const char *input);
int		handle_word(char *input, t_token **tokens);

/** lexer - Divide given input into separated tokens.
 * @input: readline output.
 * 
 * Create a new t_token list.
 * For each token :
 * - set its token->type
 * - set its token->str
 * 
 * Returns: The t_token list.
 */
t_token	*lexer(char *input)
{
	t_token			*tokens;
	int				i;

	i = 0;
	tokens = NULL;
	if (!input)
		return (NULL);
	tokens = fill_tokens(input, i, tokens);
	if (!tokens)
		return (NULL);
	return (tokens);
}

/** fill_tokens - Fill the given tokens list.
 * @input: readline output.
 * @i: current index of the cursor.
 * @tokens: the token list to add each new token to.
 * 
 * Reads the string at the current index and skip the whitespaces.
 * 
 * Depending on the case, trigger a function either 
 * to manage an operator or to manage a word.
 * A new token is created in those functions.
 * 
 * Then the current index is increased by the length of the new created token.
 * 
 * Returns: The updated t_token list, or NULL if an error occurs.
 */
t_token	*fill_tokens(char *input, int i, t_token *tokens)
{
	int	len;

	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			len = handle_operator(input + i, &tokens);
			if (!len)
				return (free_tokens(tokens), NULL);
			i += len;
		}
		else
		{
			len = handle_word(input + i, &tokens);
			if (!len)
				return (free_tokens(tokens), NULL);
			i += len;
		}
	}
	return (tokens);
}

/** extract_word_len - Get the word length.
 * @input: current pointer on the given string from readline prompt.
 *
 * The "word" is defined between unquoted operator and spaces.
 * 
 * Returns: The length (int) of the "word" token.
 */
int	extract_word_len(const char *input)
{
	int	i;
	int	quote_len;

	i = 0;
	quote_len = 0;
	if (!input)
		return (0);
	while (input[i] && !is_space(input[i]) && !is_operator(*(input + i)))
	{
		quote_len = is_closed((char *)input + i, input[i]);
		if ((input[i] == '"' || input[i] == '\'') && quote_len)
		{
			i += quote_len + 1;
		}
		else
			i++;
	}
	return (i);
}

/** handle_word - Set the current input as WORD Token.
 * @input: current read string.
 * @tokens: the list of tokens to add the new token to.
 *
 * Get the length of the word.
 * Malloc a new token, initiate it with the string as token->str.
 * Then add it to the token list.
 * 
 * Returns: the length (int) of the input set as word.
 */
int	handle_word(char *input, t_token **tokens)
{
	t_token	*new;
	int		len;
	char	*str;

	len = extract_word_len(input);
	str = ft_strndup(input, len);
	if (!str)
		return (perror("minishell"), 0);
	new = constr_new_token(T_WORD, str);
	if (!new)
		return (free(str), perror("minishell"), 0);
	free(str);
	if (!new)
		return (0);
	ft_memset(&new->data, 0, sizeof(new->data));
	add_to_tokens(new, tokens);
	return (len);
}
