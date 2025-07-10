/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:26:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:38:24 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input);
t_token	*fill_tokens(char *input, int i, t_token *tokens);
int		extract_word_len(const char *input);
int		handle_word(char *input, t_token **tokens);

/**
 * @brief Tokenize the given input string.
 *
 * @param input The string to tokenize (usually from readline).
 * @return t_token* A linked list of tokens, or NULL on error.
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

/**
 * @brief Fill the token list by parsing the input string.
 *
 * @param input The string to tokenize.
 * @param i Current position in the input string.
 * @param tokens Pointer to the current token list.
 * @return t_token* Updated token list, or NULL on error.
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

/**
 * @brief Calculate the length of the next word token.
 *
 * A "word" is defined as a sequence of characters until a space or operator,
 * considering quoted substrings as part of the word.
 *
 * @param input Pointer to the current position in the input string.
 * @return int Length of the word token.
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

/**
 * @brief Create a word token and add it to the token list.
 *
 * @param input The current position in the input string.
 * @param tokens Pointer to the token list.
 * @return int Length of the word token added, or 0 on error.
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
	ft_memset(&new->data, 0, sizeof(new->data));
	add_to_tokens(new, tokens);
	return (len);
}
