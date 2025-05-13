/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:02:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/13 12:20:51 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token);
void	free_tokens(t_token *tokens);
// void	free_token_data(t_token *token);

//new_token data = ??//TODO
t_token	*constr_new_token(t_token_type type, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->str = str;
	new_token->next = NULL;
	new_token->in_fd = 0;
	new_token->out_fd = 0;
	return (new_token);
}

void	add_to_tokens(t_token *new_token, t_token **tokens)
{
	t_token	*tmp;

	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		if (token->data)
		{
			if (token->type == T_WORD)
				free_cmd(token->data->cmd);
			else if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
				|| token->type == T_APPEND || token->type == T_HEREDOC)
				free_redir(token->data->rd);
			free(token->data);
		}
		free(token);
	}
	return ;
}

void	free_tokens(t_token *head)
{
	t_token	*cursor;

	cursor = head;
	while (head)
	{
		cursor = head->next;
		free_token(head);
		head = cursor;
	}
}

// void	free_token_data(t_token *token)
// {
// 	if (!token)
// 		return ;
// 	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
// 		|| token->type == T_APPEND || token->type == T_HEREDOC)
// 	{
// 		free(token->data->rd->is_append);
// 		free(token->data->rd->is_truncate);
// 	}
// }
