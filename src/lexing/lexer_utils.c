/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:44:34 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 14:47:38 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_space(char c);

/** is_space - Compares a char to whitespaces.
 * @c: char read.
 * 
 * Check if the read char is a white space.
 * 
 * Returns: 1 if true, 0 if false.
 */
int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}
