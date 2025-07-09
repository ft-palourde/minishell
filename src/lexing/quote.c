/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:10:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 16:12:22 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_quote(char c);
int		get_quoted_len(char quote, char *str);

/** is_quote - Read a char and return if it is a quote char.
 * @c: The char read compared to simple and double quote.
 *
 * Returns: An int as boolean, 1 true, 0 false.
 */
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/** get_quoted_len - Get the len of the str between 2 same and unescaped quotes.
 * @quote: quote set as limiter.
 * @input: str to read until limiter.
 * 
 * Returns: The len (int) of the part between same quote type.
 */
int	get_quoted_len(char quote, char *input)
{
	int	quoted_len;

	quoted_len = 1;
	while (input[quoted_len])
	{
		if (input[quoted_len] == quote)
			break ;
		quoted_len++;
	}
	if (input[quoted_len] == quote)
		quoted_len++;
	return (quoted_len);
}
