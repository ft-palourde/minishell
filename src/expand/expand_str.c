/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:03 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:02:15 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_loop(t_ms *ms, char *str, char **new, int *i);
char	*str_expand(char *str, t_ms *ms);

/**
 * @brief Internal loop for string expansion.
 *
 * Processes the string chunk by chunk and appends expanded parts.
 *
 * @param ms The minishell structure.
 * @param str The string to expand.
 * @param new Pointer to the expanded string being built.
 * @param i Pointer to current index in str (updated).
 * @return Pointer to the expanded string.
 */
char	*expand_loop(t_ms *ms, char *str, char **new, int *i)
{
	char	*tmp;
	char	*chunk;

	while (str && str[*i])
	{
		chunk = get_next_chunk(str + *i);
		if (!chunk)
			return (free(*new), NULL);
		*i += ft_strlen(chunk);
		tmp = chunk;
		chunk = expand_chunk(chunk, ms);
		if (!chunk)
			return (free(tmp), NULL);
		free(tmp);
		tmp = *new;
		*new = ft_strjoin(tmp, chunk);
		if (!*new)
			return (free(tmp), free(chunk), NULL);
		free(tmp);
		free(chunk);
	}
	return (*new);
}
/**
 * @brief Expand all variables and special characters in a string.
 *
 * Performs variable and path expansions over the entire string.
 *
 * @param str The string to expand.
 * @param ms The minishell structure.
 * @return A newly allocated string with all expansions applied.
 */
char	*str_expand(char *str, t_ms *ms)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	return (expand_loop(ms, str, &new, &i));
}
