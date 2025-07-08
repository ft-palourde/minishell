/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:14 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 11:07:33 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*parse(char *input);
static int	check_syntax_error(t_token *tokens);
static	int	invalid_first_token(t_token *tokens);
static	int	invalid_last_token(t_token *tokens);
static	void	handle_cursor(t_token *cursor);

/* ************************************************************************** */

t_token	*parse(char *input)
{
	t_token	*cursor;
	t_token	*tokens;

	if (!input || !(*input))
		return (NULL);
	tokens = lexer(input);
	if (!tokens)
		return (NULL);
	if (check_syntax_error(tokens))
		return (free_tokens(tokens), NULL);
	cursor = tokens;
	while (cursor)
	{
		handle_cursor(cursor);
		if (!cursor)
			return (free_tokens(tokens), NULL);
		cursor = cursor->next;
	}
	return (tokens);
}

static	void	handle_cursor(t_token *cursor)
{
	if (!cursor)
		return ;
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
}

/* 
returns 1 if there is a syntax error, 0 otherwise
*/
int	check_syntax_error(t_token *tokens)
{
	t_token	*cursor;

	if (!tokens)
		return (0);
	cursor = tokens;
	if (invalid_first_token(tokens) == 1)
		return (ft_putstr_fd("error : invalid first token\n", 2), 1);
	if (invalid_last_token(tokens) == 1)
		return (ft_putstr_fd("error : invalid last token\n", 2), 1);
	if (unclosed_quote(tokens) == 1)
		return (ft_putstr_fd("error : unclosed quote\n", 2), 1);
	while (cursor)
	{
		if (cursor->type == T_PIPE && (!cursor->next
				|| cursor->next->type == T_PIPE))
			return (ft_putstr_fd("unexpected token `|'\n", 2), 1);
		if (cursor->type == T_REDIR_IN || cursor->type == T_REDIR_OUT
			|| cursor->type == T_APPEND || cursor->type == T_HEREDOC)
		{
			if (!cursor->next || cursor->next->type != T_WORD)
				return (ft_putstr_fd("error: missing file after rd\n", 2), 1);
		}
		cursor = cursor->next;
	}
	return (0);
}

static	int	invalid_first_token(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == T_PIPE || tokens->type == T_AND_IF
		|| tokens->type == T_OR_IF)
		return (1);
	return (0);
}

static	int	invalid_last_token(t_token *tokens)
{
	t_token	*cursor;

	cursor = tokens;
	while (cursor->next)
		cursor = cursor->next;
	if (cursor && (cursor->type == T_PIPE || cursor->type == T_AND_IF
			|| cursor->type == T_OR_IF || cursor->type == T_REDIR_IN
			|| cursor->type == T_REDIR_OUT || cursor->type == T_APPEND
			|| cursor->type == T_HEREDOC) && cursor->next == NULL)
		return (1);
	return (0);
}
