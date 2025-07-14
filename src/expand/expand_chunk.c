/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/14 12:01:34 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			add_remains_until_next_trigger(char **new, char *str, int *i);
char		*get_next_chunk(char *str);
char		*expand_chunk(char *str, t_ms *ms);
static char	*prepare_chunk(char *str, int *quote_type);
static char	*expand_variables(char *str, t_ms *ms);

/**
 * @brief Copy characters until the next expansion trigger ($ or ~).
 *
 * @param new Pointer to the resulting string (modified).
 * @param str The string to process.
 * @param i Pointer to cursor index (updated).
 * @return 0 on success, 1 on allocation error.
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

/**
 * @brief Extract the next chunk from the string.
 *
 * A chunk is either a quoted string or a sequence without quotes.
 *
 * @param str The string to analyze.
 * @return A newly allocated string containing the next chunk.
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

/**
 * @brief Prepares a string chunk by removing surrounding quotes if necessary.
 *
 * This function checks whether the given string starts with a quote
 * (single or double). If it does, it duplicates the string without
 * the surrounding quotes. Additionally, if the string is enclosed by
 * double quotes, it trims the internal double quotes as well.
 *
 * @param str The input string to process.
 * @param quote_type Pointer to an integer where the quote type will be stored:
 *                   - 0: no quotes
 *                   - 1: single quote ('\'')
 *                   - 2: double quote ('\"')
 * @return A newly allocated string with quotes removed if necessary,
 *         or NULL on allocation failure.
 */
static char	*prepare_chunk(char *str, int *quote_type)
{
	char	*new;

	new = NULL;
	*quote_type = check_quote_type(str[0]);
	if (*quote_type == 1 || *quote_type == 2)
		new = ft_strndup(str + 1, ft_strlen(str) - 2);
	else
		new = ft_strdup(str);
	if (!new)
		return (NULL);
	return (new);
}

/**
 * @brief Expands environment variables and tilde in the given string.
 *
 * This function scans the input string for variables marked by '$' or '~',
 * replaces them with their corresponding values, and appends the remaining
 * parts of the string. The function allocates a new string containing the
 * expanded result.
 *
 * @param str The input string to process.
 * @param ms Pointer to the minishell context, containing environment variables.
 * @return A newly allocated string with variables expanded,
 *         or NULL on allocation failure or internal error.
 */
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
 * @brief Expand a single chunk of the string (with respect to quotes).
 *
 * - Removes quotes if needed.
 * - Expands variables if allowed.
 *
 * @param str The chunk to expand.
 * @param ms The minishell structure.
 * @return A newly allocated string containing the expanded chunk.
 */
char	*expand_chunk(char *str, t_ms *ms)
{
	char	*prepared;
	char	*expanded;
	int		quote_type;

	prepared = NULL;
	expanded = NULL;
	quote_type = 0;
	prepared = prepare_chunk(str, &quote_type);
	if (!prepared)
		return (NULL);
	if (quote_type == 1)
		return (prepared);
	expanded = expand_variables(prepared, ms);
	free(prepared);
	return (expanded);
}
