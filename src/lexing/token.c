/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:02:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:34:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*constr_new_token(t_token_type type, char *str);
void	add_to_tokens(t_token *new_token, t_token **tokens);
void	free_token(t_token *token);
void	free_tokens(t_token *tokens);

/**
 * @brief Construct a new token object.
 * 
 * @param type The type of the token.
 * @param str The string value of the token.
 * 
 * @return A pointer to the newly allocated t_token, or NULL on error.
 */
t_token	*constr_new_token(t_token_type type, char *str)
{
	t_token	*new_token;
	char	*dup;

	if (!str)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	dup = ft_strdup(str);
	if (!dup)
		return (free_token(new_token), NULL);
	new_token->type = type;
	new_token->str = dup;
	new_token->next = NULL;
	new_token->in_fd = STDIN_FILENO;
	new_token->out_fd = STDOUT_FILENO;
	new_token->is_piped = 0;
	return (new_token);
}

/**
 * @brief Add a new token to the end of the tokens list.
 * 
 * @param new_token The token to add.
 * @param tokens Pointer to the head of the tokens list.
 */
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

/**
 * @brief Free a single token.
 * 
 * @param token The token to free.
 */
void	free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		if (token->data)
		{
			if (token->type == T_WORD || token->type == T_CMD)
			{
				if (token->data->cmd)
					free_cmd(token->data->cmd);
			}
			else if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
				|| token->type == T_APPEND || token->type == T_HEREDOC)
				free_redir(token->data->rd);
			free(token->data);
		}
		free(token);
	}
	return ;
}

/**
 * @brief Free the entire list of tokens.
 * 
 * @param head Pointer to the head of the tokens list.
 */
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
