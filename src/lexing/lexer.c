/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:26:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/03 12:25:34 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *input);
int		handle_word(char *input, t_token **tokens);
int		is_closed(char *input, char quote);

/* 
slice the char input and returns a t_token list where each node has a token type.
*/
t_token	*lexer(char *input)
{
	t_token			*tokens;
	int				i;
	int				len;

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
		{
			len = handle_operator(input + i, &tokens);
			if (!len)
				return ;
			i += len;
		}
		else
		{
			len = handle_word(input + i, &tokens);
			if (!len)
				return ;
			i += len;
		}
	}
	return (tokens);
}

/* 
return the length of current word
*/
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

int	handle_word(char *input, t_token **tokens)
{
	t_token	*new;
	int		len;
	char	*str;

	len = extract_word_len(input);
	str = ft_strndup(input, len);
	if (!str)
		return (perror("malloc"), NULL);
	new = constr_new_token(T_WORD, str);
	if (!new)
		return (free(str), perror("malloc"), -1);
	free(str);
	if (!new)
		return (0);
	ft_memset(&new->data, 0, sizeof(new->data));
	add_to_tokens(new, tokens);
	return (len);
}
