/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:10:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/07 16:28:50 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_quote(char *input, t_token **tokens);
int		is_quote(char c);

/*
returns 1 if c == '\'' || c == '\"'
*/
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
	while (input[len])
	{
		if (input[len] == quote && !is_escaped(input, len))
			break ;
		len++;
	}
	if (input[len] == quote)
		len++;
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

// int	get_quote_len();