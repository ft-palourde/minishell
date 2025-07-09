/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:03 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 17:31:10 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_expand(char *str, t_ms *ms);

/** expand_loop - .
 * @param ms The minishell structure.
 * @param str The string to expand.
 * @param new The array to add the expansion to.
 * @param i The line cursor.
 * 
 * Divide the string into several chunks.
 * Expand each chunk.
 * Add each result to the string builder.
 *
 * @returns the string.
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

/** @brief str_expand - Replace each expandable variable by its value.
 * 
 * @param str The string to expand.
 * @param ms The minishell structure.
 * 
 * Create a new string, divide the string into several chunks.
 * Expand each chunk then add the result to the string.
 *
 * @returns the new string with expanded values.
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
