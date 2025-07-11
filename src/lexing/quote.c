/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:10:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:39:38 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_quote(char c);
int		get_quoted_len(char quote, char *str);

/**
 * @brief Check if the character is a quote character.
 *
 * @param c The character to check.
 * @return int 1 if it is a quote, 0 otherwise.
 */
int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

/**
 * @brief Get the length of the substring enclosed by the given quote character.
 *
 * This function assumes the starting quote is already matched and counts
 * characters until the closing quote of the same type.
 *
 * @param quote The quote character used as a delimiter.
 * @param input The string to parse.
 * @return int The length of the quoted substring, including the closing quote.
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
