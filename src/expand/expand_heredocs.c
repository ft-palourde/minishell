/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:19:06 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/09 18:29:31 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** @brief hd_var_expand - Expands a variable in the given string.
 * @param str The string containing the variable to expand.
 * @param env The grid of environment variables.
 * 
 * This function checks if the string starts with a '$' character,
 * extracts the variable name, retrieves its value, and constructs
 * a new string with the expanded value.
 *
 * @returns A newly allocated string with the expanded variable,
 * or NULL on failure.
 */
char	*hd_var_expand(char *str, t_ms *ms)
{
	char	*var_value;
	char	*var_name;
	int		i;

	if (!str || str[0] != '$')
		return (ft_strdup(str));
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	var_value = var_name_to_value(var_name, ms);
	free(var_name);
	return (var_value);
}

/** @brief hd_add_var_to_new - update the expanded string to build in hd.
 * 
 * @param new the string to add expanded variables to.
 * @param str the string to expand.
 * @param i the line cursor to update.
 * @param ms the minishell structure.
 *  
 */
void	hd_add_var_to_new(char **new, char *str, t_ms *ms)
{
	char	*tmp;
	char	*var;

	var = hd_var_expand(str, ms);
	tmp = *new;
	*new = ft_strjoin(*new, var);
	free(tmp);
	free(var);
}

/** @brief add_quote_to_new - Add quotes at beginning and end of hd content.
 * @param quote the specific quote char (simple or double)
 * @param new the final string to build.
 */
int	add_quote_to_new(char quote, char **new)
{
	char	*tmp;
	char	*c;

	c = ft_calloc(sizeof(char), 2);
	if (!c)
		return (perror("minishell"), 1);
	c[0] = quote;
	tmp = *new;
	*new = ft_strjoin(*new, c);
	free(tmp);
	if (!*new)
		perror("minishell");
	free(c);
	return (1);
}

/** hd_expand_chunk - expand the given chunk in heredoc case.
 * @param str The string to expand.
 * @param ms The minishell structure.
 * 
 * @returns the expanded chunk to add to the string builder.
 */
char	*hd_expand_chunk(char *str, t_ms *ms)
{
	char	*new;
	int		i;
	int		quote;
	int		expand;

	quote = (str[0] == '\'' || str[0] == '\"');
	i = 0;
	expand = 0;
	while (str[i] && str[i] != '$')
		i++;
	new = ft_strndup(str, i);
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '~')
		{
			expand = 1;
			hd_add_var_to_new(&new, str + i, ms);
			i++;
		}
		while (str[i] && str[i] != '$')
			i++;
	}
	if (quote && expand)
		add_quote_to_new(str[0], &new);
	return (new);
}

/** @brief hd_expand - Browse and expand each argument of given cmd.
 * 
 * @param str The str to expand.
 * @param ms The minishell structure.
 * 
 * @returns the expanded string or NULL if malloc failed.
 */
char	*hd_expand(t_ms *ms, char *str)
{
	char	*new;
	char	*tmp;
	char	*chunk;
	int		i;

	i = 0;
	new = ft_strdup("");
	while (str && str[i])
	{
		chunk = get_next_chunk(str + i);
		i += ft_strlen(chunk);
		tmp = chunk;
		chunk = hd_expand_chunk(chunk, ms);
		free(tmp);
		tmp = new;
		new = ft_strjoin(new, chunk);
		free(tmp);
		free(chunk);
		if (!new)
			return (NULL);
	}
	return (new);
}
