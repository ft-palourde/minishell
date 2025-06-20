/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 14:30:54 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_name_to_value(char *name, t_ms *ms);
char	*var_expand(char *str, t_ms *ms);
void	add_var_to_new(char **new, char *str, t_ms *ms);

/** var_expand - Expands a variable in the given string.
 * @str: The string containing the variable to expand.
 * @env: The grid of environment variables.
 * 
 * This function checks if the string starts with a '$' character,
 * extracts the variable name, retrieves its value, and constructs
 * a new string with the expanded value.
 *
 * Returns: A newly allocated string with the expanded variable,
 * or NULL on failure.
 */
char	*var_expand(char *str, t_ms *ms)
{
	char	*var_value;
	char	*var_name;
	int		i;

	if (!str || (str[0] != '$' && str[0] != '~'))
		return (ft_strdup(str));
	i = 1;
	if (str[0] == '~')
		return (expand_path(str, ms));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	var_value = var_name_to_value(var_name, ms);
	free(var_name);
	return (var_value);
}

/** var_name_to_value - Expands a variable in the given string.
 * @name: The string containing the variable to expand.
 * @env: The grid of environment variables.
 * 
 * This function browse the environment variable list,
 * finds the variable by name, retrieves its value, and constructs
 * a new string with the variable value.
 *
 * Returns: A newly allocated string with the value of the variable,
 * or NULL if the name doesn't match any.
 */
char	*var_name_to_value(char *name, t_ms *ms)
{
	int		i;
	int		len;
	char	*value;

	len = ft_strlen(name);
	i = 0;
	value = NULL;
	while (ms->env[i])
	{
		if (!ft_strncmp(name, ms->env[i], len) && ms->env[i][len] == '=')
			break ;
		i++;
	}
	if (ms->env[i])
	{
		value = get_var_value(ms->env[i]);
		if (!value)
			return (perror("malloc"), NULL);
	}
	else
		return (ft_strdup(""));
	return (value);
}

void	add_var_to_new(char **new, char *str, t_ms *ms)
{
	char	*tmp;
	char	*var;

	var = var_expand(str, ms);
	tmp = *new;
	*new = ft_strjoin(*new, var);
	free(tmp);
	free(var);
}
