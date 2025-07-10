/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:14 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 23:04:20 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*parse(char *input);
static int	check_syntax_error(t_token *tokens);
static	int	invalid_first_token(t_token *tokens);
static	int	invalid_last_token(t_token *tokens);
static	int	handle_cursor(t_token *cursor);

/**
 * @brief Parse the input string into a token list and check syntax errors.
 * 
 * @param input Input string to parse.
 * 
 * @return Pointer to the head of the token list, or NULL on error.
 */
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
		if (handle_cursor(cursor))
			return (free_tokens(tokens), NULL);
		cursor = cursor->next;
	}
	return (tokens);
}

/**
 * @brief Handle a token during parsing, dispatching according to its type.
 * 
 * @param cursor Current token to handle.
 * 
 * @return 0 on success, 1 on failure.
 */
static	int	handle_cursor(t_token *cursor)
{
	int	err;

	err = 0;
	if (!cursor)
		return (1);
	if (cursor->type == T_REDIR_IN || cursor->type == T_REDIR_OUT
		|| cursor->type == T_APPEND)
		err = parse_rd_file(cursor);
	else if (cursor->type == T_HEREDOC)
		err = parse_heredoc(cursor);
	else if (cursor->type == T_PIPE)
		cursor->data = NULL;
	else if (cursor->type == T_AND_IF || cursor->type == T_OR_IF)
		cursor->data = NULL;
	else if (cursor->type == T_WORD)
		err = parse_cmd(cursor);
	return (err);
}

/**
 * @brief Check the token list for syntax errors.
 * 
 * @param tokens Head of the token list.
 * 
 * @return 1 if syntax error detected, 0 otherwise.
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
			return (ft_putstr_fd("error : unexpected token `|'\n", 2), 1);
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

/** 
 * @brief Check if the first token is an invalid logic operator.
 * 
 * This function checks whether the first token in the list is a logical operator
 * that cannot start a command line, such as a pipe (`|`), logical AND (`&&`),
 * or logical OR (`||`). Starting with these tokens is considered a syntax error.
 * 
 * @param tokens Pointer to the head of the token linked list.
 * 
 * @return 1 if the first token is an invalid logic token, 0 otherwise.
 */
static	int	invalid_first_token(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (tokens->type == T_PIPE || tokens->type == T_AND_IF
		|| tokens->type == T_OR_IF)
		return (1);
	return (0);
}

/**
 * @brief Check if the last token is an invalid logic or redirection token.
 * 
 * This function traverses the token list to find the last token 
 * and verifies if it is a logic operator (`|`, `&&`, `||`)
 * or a redirection operator (`<`, `>`, `>>`, `<<`).
 * Ending a command line with such tokens is considered a syntax error.
 * 
 * @param tokens Pointer to the head of the token linked list.
 * 
 * @return 1 if the last token is an invalid logic or redirection token, 
 * 0 otherwise.
 */
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
