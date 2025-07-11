/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:11:50 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:54:47 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_tokens(t_token *tokens);
static char	*get_token_type_str(t_token *token);
void		debug_display_token_args(t_token *tokens);
void		debug_display_token_cmd(t_token *token, char *type_str);
void		debug_display_token_rd(t_token *token, char *type_str);

/**
 * @brief Display a list of tokens and their types for debugging.
 * 
 * @param tokens Head of the token list.
 */
void	display_tokens(t_token *tokens)
{
	t_token	*cursor;
	char	*type_str;

	if (!tokens)
	{
		printf("No tokens\n");
		return ;
	}
	cursor = tokens;
	while (cursor)
	{
		type_str = get_token_type_str(cursor);
		printf("\nToken: %s - Type : %s\n", cursor->str, type_str);
		cursor = cursor->next;
	}
}

/**
 * @brief Helper function to get a string representation of a token type.
 * 
 * @param token Token to analyze.
 * 
 * @return String corresponding to the token type.
 */
static char	*get_token_type_str(t_token *token)
{
	if (token->type == T_WORD)
		return ("WORD");
	else if (token->type == T_PIPE)
		return ("PIPE");
	else if (token->type == T_AND_IF)
		return ("AND_IF");
	else if (token->type == T_OR_IF)
		return ("OR_IF");
	else if (token->type == T_REDIR_IN)
		return ("REDIR_IN");
	else if (token->type == T_REDIR_OUT)
		return ("REDIR_OUT");
	else if (token->type == T_APPEND)
		return ("APPEND");
	else if (token->type == T_HEREDOC)
		return ("HEREDOC");
	else if (token->type == T_CMD)
		return ("T_CMD");
	else
		return ("UNKNOWN");
}

/**
 * @brief Debug function to display tokens with their arguments and redirections.
 * 
 * @param tokens Head of the token list.
 */
void	debug_display_token_args(t_token *tokens)
{
	t_token	*cursor;
	char	*type_str;

	printf("\nDisplay token args:\n");
	if (!tokens)
	{
		printf("No tokens\n");
		return ;
	}
	cursor = tokens;
	while (cursor)
	{
		printf("\n[\n");
		type_str = get_token_type_str(cursor);
		if (cursor->type == T_CMD && cursor->data && cursor->data->cmd)
			debug_display_token_cmd(cursor, type_str);
		else if (cursor->type == T_REDIR_IN || cursor->type == T_REDIR_OUT
			|| cursor->type == T_APPEND || cursor->type == T_HEREDOC)
			debug_display_token_rd(cursor, type_str);
		else
			printf("Token: %s - Type : %s\n", cursor->str, type_str);
		cursor = cursor->next;
		printf("]\n");
	}
}

/**
 * @brief Display the arguments of a command token for debugging.
 * 
 * @param token Command token.
 * @param type_str String representation of the token type.
 */
void	debug_display_token_cmd(t_token *token, char *type_str)
{
	int	i;

	if (token->type == T_CMD && token->data && token->data->cmd)
	{
		i = 0;
		printf("Token: %s - Type : %s\n", token->str, type_str);
		while (token->data->cmd->args[i])
		{
			printf("Arg [%d]: %s\n", i, token->data->cmd->args[i]);
			i++;
		}
	}
	return ;
}

/**
 * @brief Display the details of a redirection token for debugging.
 * 
 * @param token Redirection token.
 * @param type_str String representation of the token type.
 */
void	debug_display_token_rd(t_token *token, char *type_str)
{
	if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
		|| token->type == T_APPEND)
	{
		printf("Token: %s - Type : %s\n", token->str, type_str);
		if (token->data && token->data->rd->file)
		{
			printf("File: %s\n", token->data->rd->file->filename);
			printf("FD: %d\n", token->data->rd->file->fd);
		}
	}
	else if (token->type == T_HEREDOC)
	{
		printf("Token: %s - Type : %s\n", token->str, type_str);
		if (token->data && token->data->rd->heredoc)
		{
			printf("Lim: %s\n", token->data->rd->heredoc->lim);
		}
	}
	return ;
}
