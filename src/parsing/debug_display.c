/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:11:50 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/01 18:20:29 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_tokens(t_token *tokens);
static char	*get_token_type_str(t_token *token);
void		debug_display_token_args(t_token *tokens);

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
	int		i;
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
		type_str = get_token_type_str(cursor);
		if (cursor->type == T_WORD && cursor->data && cursor->data->cmd)
		{
			i = 0;
			printf("Token: %s - Type : %s\n", cursor->str, type_str);
			while (cursor->data->cmd->args[i])
			{
				printf("Arg [%d]: %s\n", i, cursor->data->cmd->args[i]);
				i++;
			}
		}
		else
			printf("Token: %s - Type : %s\n", cursor->str, type_str);
		cursor = cursor->next;
	}
}
