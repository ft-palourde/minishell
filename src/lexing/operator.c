/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:39:54 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 16:10:37 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				handle_operator(char *input, t_token **tokens);
t_token_type	get_operator_type(char *input);
int				operator_len(t_token_type type);
bool			is_operator(char c);

/** @brief handle_operator - Set the current Operator Token.
 * @param input current read string.
 * @param tokens the list of tokens to add the new token to.
 *
 * Get the operator type.
 * Malloc a new token, initiate it with the string as token->str.
 * Then add it to the token list.
 * 
 * @returns (int) len : the length of the input set as token.
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

/** @brief is_operator - Read a char and return if it is an operator.
 * @param c The char read compared to operator symbols.
 *
 * @returns An int as boolean, 1 true, 0 false.
 */
bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

/** @brief get_operator_type - Read and returns the type of given input.
 * @param input The string read compared to operator symbols.
 *
 * @returns t_token_type The type of given input.
 */
t_token_type	get_operator_type(char *input)
{
	if (!ft_strncmp(input, "&&", 2))
		return (T_AND_IF);
	if (!ft_strncmp(input, "||", 2))
		return (T_OR_IF);
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

/** @brief operator_len - Give the operator length.
 * @param type The type of the token to observe.
 *
 * @returns the length (int) of the operator.
 */
int	operator_len(t_token_type type)
{
	if (type == T_AND_IF || type == T_OR_IF
		|| type == T_APPEND || type == T_HEREDOC)
		return (2);
	return (1);
}
