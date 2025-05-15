/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:14 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/15 10:56:59 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*parse(char *input);
static int	check_syntax_error(t_token *tokens);
void		parse_rd_file(t_token *token);
void		parse_heredoc(t_token *token);

/* ************************************************************************** */

t_token	*parse(char *input)
{
	t_token	*cursor;
	t_token	*tokens;

	tokens = lexer(input);
	cursor = tokens;
	while (cursor)
	{
		if (check_syntax_error(cursor))
			return (free_tokens(tokens), NULL);
		if (cursor->type == T_REDIR_IN || cursor->type == T_REDIR_OUT
			|| cursor->type == T_APPEND)
			parse_rd_file(cursor);
		else if (cursor->type == T_HEREDOC)
			parse_heredoc(cursor);
		else if (cursor->type == T_PIPE)
			cursor->data = NULL;
		else if (cursor->type == T_AND_IF || cursor->type == T_OR_IF)
			cursor->data = NULL;
		else if (cursor->type == T_WORD)
			parse_cmd(cursor);
		if (!cursor)
			break ;
		cursor = cursor->next;
	}
	return (tokens);
}

/* 
returns 1 if there is a syntax error, 0 otherwise
*/
int	check_syntax_error(t_token *tokens)
{
	t_token	*cursor;

	cursor = tokens;
	if (tokens->type == T_PIPE)
		return (ft_putstr_fd("error : first token cannot be `|'\n", 2), 1);
	while (cursor)
	{
		if (cursor->type == T_PIPE && (!cursor->next
				|| cursor->next->type == T_PIPE))
		{
			ft_putstr_fd("unexpected token `|'\n", 2);
			return (1);
		}
		if (cursor->type == T_REDIR_IN || cursor->type == T_REDIR_OUT
			|| cursor->type == T_APPEND || cursor->type == T_HEREDOC)
		{
			if (!cursor->next || cursor->next->type != T_WORD)
			{
				ft_putstr_fd("syntax error: missing file after rd\n", 2);
				return (1);
			}
		}
		cursor = cursor->next;
	}
	return (0);
}
