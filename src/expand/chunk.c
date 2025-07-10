/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 17:27:51 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_next_chunk(char *str);
char		*expand_chunk(char *str, t_ms *ms);
// static int	skip_until_next_trigger(char *str, int *i);

/** add_remains_until_next_trigger - Add non expandable string to expand retval.
 * @param new The string pointer to add the remains to.
 * @param str the remains after expand.
 * @param i the string cursor.
 * 
 * Add in the string builder any non expandable string.
 *
 * @returns 1 if error, 0 otherwise.
 */
int	add_remains_until_next_trigger(char **new, char *str, int *i)
{
	char	*remain;
	char	*tmp;
	int		len;
	int		j;

	if (!str[*i])
		return (0);
	j = 0;
	len = 0;
	while (str[*i + len] && str[*i + len] != '$' && str[*i + len] != '~')
		len++;
	remain = ft_calloc(len + 1, sizeof(char));
	if (!remain)
		return (1);
	while (j < len)
	{
		remain[j] = str[*i + j];
		j++;
	}
	tmp = *new;
	*new = ft_strjoin(*new, remain);
	if (!*new)
		return (free(tmp), free(remain), 1);
	*i += len;
	return (free(tmp), free(remain), 0);
}

/** @brief get_next_chunk - Get the next quoted or unquoted expandable chunk.
 * 
 * @param str: The string to be read.
 *
 * @returns the chunk (str) to expand.
 */
char	*get_next_chunk(char *str)
{
	int		i;
	char	*chunk;

	i = 0;
	if (str[0] == '\'' || str[0] == '\"')
		i = is_closed(str, str[0]) + 1;
	else
	{
		while (str[i])
		{
			if ((str[i] == '\'' || str[i] == '\"'))
				break ;
			i++;
		}
	}
	chunk = ft_strndup(str, i);
	if (!chunk)
		return (perror("minishell"), NULL);
	return (chunk);
}

/** expand_chunk - expand the given chunk.
 * @param str The string to expand.
 * @param ms The minishell structure.
 * 
 * @returns the expanded chunk to add to the string builder.
 */
char	*expand_chunk(char *str, t_ms *ms)
{
	char	*new;
	int		quote_type;
	int		i;
	char	*trim;
	char	*expanded_chunk;

	expanded_chunk = NULL;
	i = 0;
	quote_type = check_quote_type(str[0]);
	if (quote_type == 1 || quote_type == 2)
		new = ft_strndup(str + 1, ft_strlen(str) - 2);
	else
		new = ft_strdup(str);
	if (!new)
		return (NULL);
	if (quote_type == 2)
	{
		trim = ft_strtrim(new, "\"");
		if (!trim)
			return (NULL);
		free(new);
		new = trim;
	}
	if (quote_type == 1)
		return (new);
	expanded_chunk = ft_strdup("");
	if (!expanded_chunk)
		return (NULL);
	while (new[i])
	{
		if (new[i] == '$' || new[i] == '~')
			add_var_to_new(&expanded_chunk, new, &i, ms);
		if (add_remains_until_next_trigger(&expanded_chunk, new, &i))
			return (perror("minishell"), NULL);
	}
	return (expanded_chunk);
}
