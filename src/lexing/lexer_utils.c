/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:44:34 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:37:01 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_space(char c);

/**
 * @brief Check if the given character is a whitespace character.
 *
 * @param c The character to check.
 * @return int 1 if the character is a whitespace, 0 otherwise.
 */
int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}
