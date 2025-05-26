/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:59:06 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/26 16:30:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quote(t_token *token);
int	check_quote_error(char *str, char c);
int	is_closed(char *str, char c);

/*
checks if the quote, double quote or parenthesis has a closing occurence
returns adress if found, 0 otherwise
*/
int	is_closed(char *str, char c)
{
	int		i;

	i = 1;
	if (c == '(')
		c = ')';
	while (str[i] != c && str[i])
		i++;
	if (str[i] && is_escaped(str, i))
		return (i);
	return (0);
}

int	unclosed_quote(t_token *token)
{
	t_token	*cursor;
	int		i;

	cursor = token;
	while (cursor)
	{
		if (token->type == T_CMD)
		{
			i = 0;
			while (cursor->data->cmd->args[i])
			{
				if (check_quote_error(cursor->data->cmd->args[i], '\'')
					|| check_quote_error(cursor->data->cmd->args[i], '\"'))
					return (1);
				i++;
			}
		}
		cursor = cursor->next;
	}
	return (0);
}

int	check_quote_error(char *str, char c)
{
	int	valid_quote;
	int	i;

	i = 0;
	valid_quote = 0;
	while (str[i])
	{
		if (str[i] == c && !is_escaped(str, i))
			valid_quote++;
		i++;
	}
	return (valid_quote % 2);
}
