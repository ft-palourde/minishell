/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:09:19 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/15 11:37:52 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_word(t_token *token);
void	clean_arg_tokens(t_token *token);
void	skip_rd_token_and_data(t_token *token, t_token *prev);
int		is_redir_or_hd(t_token *token);
t_token	*remove_token(t_token *prev, t_token *token);

/**
 * @brief Check if a token is of type T_WORD.
 * 
 * @param token Token to check.
 * 
 * @return 1 if token is a word, 0 otherwise.
 */
int	is_word(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_WORD)
		return (1);
	return (0);
}

void	clean_arg_tokens(t_token *token)
{
	t_token	*prev;
	int		i;

	i = 0;
	prev = token;
	while (token && token->type != T_PIPE)
	{
		if (is_redir_or_hd(token))
		{
			prev = token->next;
			token = token->next->next;
		}
		else if (token && token->type == T_WORD && i > 0)
			token = remove_token(prev, token);
		else
		{
			prev = token;
			if (token)
				token = token->next;
		}
		i++;
	}
}

void	skip_rd_token_and_data(t_token *token, t_token *prev)
{
	prev = token->next;
	token = token->next->next;
}

int	is_redir_or_hd(t_token *token)
{
	return (token
		&& (token->type == T_REDIR_IN || token->type == T_HEREDOC
			|| token->type == T_REDIR_OUT || token->type == T_APPEND));
}

t_token	*remove_token(t_token *prev, t_token *token)
{
	t_token	*next;

	prev->next = token->next;
	next = token->next;
	free_token(token);
	return (next);
}
/* 	while (token)
	{
		while (token->next && token->next->type != T_PIPE)
		{
			if (token->next->type == T_WORD && !(token->type == T_REDIR_IN
					|| token->type == T_HEREDOC || token->type == T_REDIR_OUT
					|| token->type == T_APPEND))
			{
				tmp = token->next;
				token->next = token->next->next;
				free_token(tmp);
			}
		}
		token = token->next;
	} */