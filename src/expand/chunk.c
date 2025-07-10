/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 21:19:59 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_next_chunk(char *str);
char		*expand_chunk(char *str, t_ms *ms);
static char	*prepare_chunk(char *str, int *quote_type);
static char	*expand_variables(char *str, t_ms *ms);
int			add_remains_until_next_trigger(char **new, char *str, int *i);

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
static char	*prepare_chunk(char *str, int *quote_type)
{
	char	*new;
	char	*trim;

	new = NULL;
	trim = NULL;
	*quote_type = check_quote_type(str[0]);
	if (*quote_type == 1 || *quote_type == 2)
		new = ft_strndup(str + 1, ft_strlen(str) - 2);
	else
		new = ft_strdup(str);
	if (!new)
		return (NULL);
	if (*quote_type == 2)
	{
		trim = ft_strtrim(new, "\"");
		if (!trim)
			return (free(new), NULL);
		free(new);
		new = trim;
	}
	return (new);
}

static char	*expand_variables(char *str, t_ms *ms)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '~')
			add_var_to_new(&new, str, &i, ms);
		if (add_remains_until_next_trigger(&new, str, &i))
			return (perror("minishell"), free(new), NULL);
	}
	return (new);
}

char	*expand_chunk(char *str, t_ms *ms)
{
	char	*prepared;
	char	*expanded;
	int		quote_type;

	prepared = NULL;
	expanded = NULL;
	prepared = prepare_chunk(str, &quote_type);
	if (!prepared)
		return (NULL);
	if (quote_type == 1)
		return (prepared);
	expanded = expand_variables(prepared, ms);
	free(prepared);
	return (expanded);
}
