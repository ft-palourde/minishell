/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/26 19:05:47 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_backslash(char c);
int		is_escaped(char *input, int index);

int	is_backslash(char c)
{
	return (c == '\\');
}

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
