/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:39:54 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/27 12:55:55 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				handle_operator(char *input, t_token **tokens);
t_token_type	get_operator_type(char *input);
int				operator_len(t_token_type type);
bool			is_operator(char c);

int	handle_operator(char *input, t_token **tokens)
{
	t_token_type	type;
	int				len;
	t_token			*new;
	char			*str;

	type = get_operator_type(input);
	len = operator_len(type);
	str = ft_strndup(input, len);
	new = constr_new_token(type, str);
	if (!new)
		return (0);
	ft_memset(&new->data, 0, sizeof(new->data));
	add_to_tokens(new, tokens);
	return (len);
}

// check for &, |, <, >
bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

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

int	operator_len(t_token_type type)
{
	if (type == T_AND_IF || type == T_OR_IF
		|| type == T_APPEND || type == T_HEREDOC)
		return (2);
	return (1);
}
