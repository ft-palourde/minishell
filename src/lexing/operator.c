/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:39:54 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:39:17 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				handle_operator(char *input, t_token **tokens);
t_token_type	get_operator_type(char *input);
int				operator_len(t_token_type type);
bool			is_operator(char c);

/**
 * @brief Handle an operator token and add it to the token list.
 *
 * @param input Current position in the input string.
 * @param tokens Pointer to the token list.
 * @return int Length of the operator token, or 0 on error.
 */
int	handle_operator(char *input, t_token **tokens)
{
	t_token_type	type;
	int				len;
	t_token			*new;
	char			*str;

	type = get_operator_type(input);
	len = operator_len(type);
	str = ft_strndup(input, len);
	if (!str)
		return (0);
	new = constr_new_token(type, str);
	free(str);
	if (!new)
		return (0);
	ft_memset(&new->data, 0, sizeof(new->data));
	add_to_tokens(new, tokens);
	return (len);
}

/**
 * @brief Check if the given character is a shell operator.
 *
 * @param c The character to check.
 * @return true if it is an operator, false otherwise.
 */
bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Determine the type of an operator token.
 *
 * @param input Pointer to the current position in the input string.
 * @return t_token_type The type of the operator token.
 */
t_token_type	get_operator_type(char *input)
{
	if (!ft_strncmp(input, ">>", 2))
		return (T_APPEND);
	if (!ft_strncmp(input, "<<", 2))
		return (T_HEREDOC);
	if (*input == '|')
		return (T_PIPE);
	if (*input == '<')
		return (T_REDIR_IN);
	if (*input == '>')
		return (T_REDIR_OUT);
	return (T_UNKNOWN);
}

/**
 * @brief Get the length of an operator token based on its type.
 *
 * @param type The token type.
 * @return int The length of the operator token.
 */
int	operator_len(t_token_type type)
{
	if (type == T_AND_IF || type == T_OR_IF
		|| type == T_APPEND || type == T_HEREDOC)
		return (2);
	return (1);
}
