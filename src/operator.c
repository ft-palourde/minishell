/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:39:54 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/18 18:14:35 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				handle_operator(char *input, t_token **tokens);
t_token_type	get_operator_type(char *input);
int				operator_len(t_token_type type);
bool			is_operator(char c);

// check for &, |, <, >
bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

t_token_type	get_operator_type(char *input)
{
	if (!strncmp(input, "&&", 2))
		return (T_AND_IF);
	if (!strncmp(input, "||", 2))
		return (T_OR_IF);
	if (!strncmp(input, ">>", 2))
		return (T_APPEND);
	if (!strncmp(input, "<<", 2))
		return (T_HEREDOC);
	if (*input == '|')
		return (T_PIPE);
	if (*input == '<')
		return (T_REDIR_IN);
	if (*input == '>')
		return (T_REDIR_OUT);
	return (T_UNKNOWN);
}

int	operator_len(t_token_type type)
{
	if (type == T_AND_IF || type == T_OR_IF
		|| type == T_APPEND || type == T_HEREDOC)
		return (2);
	return (1);
}

/* void	handle_operator(char *input, t_token **tokens)
{
	t_token_type	type;
	int				len;
	char			*op_str;
	t_token			*new_token;

	type = get_operator_type(input);
	if (type == T_UNKNOWN)
		return ;
	len = operator_len(type);
	op_str = ft_strndup((const char *)input, len);
	if (!op_str)
		return ;
	new_token = constr_new_token(type, op_str);
	if (!new_token)
		return ;
	add_to_tokens(new_token, tokens);
	*input += len;
} */
