/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 15:15:57 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_backslash(char c);
int		is_escaped(char *input, int index);

/** is_backslash - Compares a char to backslash.
 * @c: char read.
 * 
 * Check if the read char is a backslash.
 * 
 * Returns: 1 if true, 0 if false.
 */
int	is_backslash(char c)
{
	return (c == '\\');
}

/** is_escaped - Check if the current char is escaped.
 * @input: string read.
 * @index: index of the char to check.
 * 
 * Check if there is a previous char and if it is a backslash.
 * A backslash cancels a backslash, then the backslashes are ignored by couple.
 * 
 * Returns: 1 if true, 0 if false.
 */
int	is_escaped(char *input, int index)
{
	int	is_escaped;

	is_escaped = 0;
	index--;
	while (index >= 0 && is_backslash(input[index]))
	{
		is_escaped++;
		index--;
	}
	return (is_escaped % 2);
}
