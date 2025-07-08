/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:09:19 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 14:50:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_word(t_token *token);

/** is_word - Compares a token type to T_WORD.
 * @token: the token to check the type to.
 * 
 * Check if the given token's type is T_WORD.
 * 
 * Returns: 1 if true, 0 if false.
 */
int	is_word(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_WORD)
		return (1);
	return (0);
}
