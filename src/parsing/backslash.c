/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:43:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/24 11:00:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		handle_backslash(char *input, t_token **tokens);
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
	is_escaped = is_escaped % 2;
	return (is_escaped);
}
