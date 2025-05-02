/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:11:50 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/02 11:34:34 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_tokens(t_token *tokens);
static char	*get_token_type_str(t_token *token);
void		debug_display_token_args(t_token *tokens);
void		debug_display_token_cmd(t_token *token, char *type_str);

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
		{
			debug_display_token_cmd(cursor, type_str);
		}
		else
			printf("Token: %s - Type : %s\n", cursor->str, type_str);
		cursor = cursor->next;
		printf("]\n");
	}
}

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
