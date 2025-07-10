/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:09:19 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:56:40 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_word(t_token *token);

/**
 * @brief Check if a token is of type T_WORD.
 * 
 * @param token Token to check.
 * 
 * @return 1 if token is a word, 0 otherwise.
 */
int	is_word(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_WORD)
		return (1);
	return (0);
}
