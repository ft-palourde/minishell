/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:26:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/18 19:37:04 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input);
int		handle_word(char *input, t_token **tokens);
int		handle_quote(char *input, t_token **tokens);
int		is_quote(char c);
int		is_closed(char *input, char quote);

// pour chaque token : str == contenu brut du token
// data : initialement vide, sera peut être rempli plus tard lors du parsing
// type

/* 
while (*input)
{
	skip_spaces();

	if (is_quote(*input))
		handle_quoted_word(&input, &token_list);
	else if (is_operator(input))
		handle_operator(&input, &token_list);
	else
		handle_word(&input, &token_list);
}
*/

// t_token	*lexer(void)
t_token	*lexer(char *input)
{
	t_token			*tokens;
	int				i;

	i = 0;
	tokens = NULL;
	if (!input)
		return (NULL);
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			i += handle_operator(input + i, &tokens);
		else if (is_quote(input[i]))
			i += handle_quote(input + i, &tokens);
		else
			i += handle_word(input + i, &tokens);
	}
	return (tokens);
}

int	handle_operator(char *input, t_token **tokens)
{
	t_token_type	type;
	int				len;
	t_token			*new;

	type = get_operator_type(input);
	// if (type == T_UNKNOWN)
	// 	return quelle value pour signifier error? -1 ?//TODO
	len = operator_len(type);
	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = type;
	new->str = ft_strndup(input, len);
	new->next = NULL;
	ft_memset(&new->data, 0, sizeof(new->data));
	add_to_tokens(new, tokens);
	return (len);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	handle_quote(char *input, t_token **tokens)
{
	t_token			*new_token;
	int				len;
	char			quote;

	len = 1;
	quote = *input;
	while (input[len] && input[len] != quote)
		len++;
	if (input[len] == quote)
		len++;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->type = T_WORD;
	new_token->str = ft_strndup(input, len);
	new_token->next = NULL;
	ft_memset(&new_token->data, 0, sizeof(new_token->data));
	add_to_tokens(new_token, tokens);
	return (len);
}

int	extract_word_len(const char *input)
{
	int	i;
	int	quote_len;

	i = 0;
	quote_len = 0;
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

int	is_closed(char *input, char quote)
{
	int	i;

	i = 1;
	while (input[i])
	{
		if (input[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

int	handle_word(char *input, t_token **tokens)
{
	t_token	*new;
	int		len;

	len = extract_word_len(input);
	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = T_WORD;
	new->str = ft_strndup(input, len);
	new->next = NULL;
	memset(&new->data, 0, sizeof(new->data));
	add_to_tokens(new, tokens);
	return (len);
}
