/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:02:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/21 14:53:40 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//new_token data = ??//TODO
t_token	*constr_new_token(t_token_type type, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->str = str;
	new_token->next = NULL;
	return (new_token);
}

void	add_to_tokens(t_token *new_token, t_token **tokens)
{
	t_token	*tmp;

	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}
