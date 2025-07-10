/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 21:52:00 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copy characters until the next expansion trigger ($ or ~).
 *
 * @param new Pointer to the resulting string (modified).
 * @param str The string to process.
 * @param i Pointer to cursor index (updated).
 * @return 0 on success, 1 on allocation error.
 */
int	add_remains_until_next_trigger(char **new, char *str, int *i);

/**
 * @brief Extract the next chunk from the string.
 *
 * A chunk is either a quoted string or a sequence without quotes.
 *
 * @param str The string to analyze.
 * @return A newly allocated string containing the next chunk.
 */
char	*get_next_chunk(char *str);

/**
 * @brief Expand a single chunk of the string (with respect to quotes).
 *
 * - Removes quotes if needed.
 * - Expands variables if allowed.
 *
 * @param str The chunk to expand.
 * @param ms The minishell structure.
 * @return A newly allocated string containing the expanded chunk.
 */
char	*expand_chunk(char *str, t_ms *ms);

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

/**
 * @brief Main function to expand a string in the minishell.
 *
 * This function performs the full expansion process:
 * 1. It processes quotes to determine whether to allow variable expansion.
 * 2. If allowed, it expands environment variables.
 *
 * @param str The input string to expand.
 * @param ms Pointer to the minishell state containing environment variables.
 *
 * @return A new expanded string, or NULL on error.
 */
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
