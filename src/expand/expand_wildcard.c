/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:19 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/01 18:26:04 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

/* 
expand_wildcard()
expands globbing patterns in the given string.
seul la wildcard * est à gérer
les chemins relatifs ne sont pas à convertir en absolu
*/
int	expand_wildcard(void);

int	expand_wildcard(void)
{
	return (1);
}

//pas de expand wildcard dans hd
// Fonction de matching avec wildcard '*'
// readdir, closedir
// https://pubs.opengroup.org/onlinepubs/7908799/xsh/readdir.html
// files = expand_wildcard
/** match_pattern - tests if a pattern matches a str
 * @pattern:
 * @str:
 * If we arrive to the end of the string, it matches.
 * If pattern is * :
 * - if * doesnt match any char, go forward in pattern
*/
int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*')
	{
		return (match_pattern(pattern + 1, str)
			|| (*str && match_pattern(pattern, str + 1)));
	}
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}
