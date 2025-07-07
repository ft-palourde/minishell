/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/04 16:51:20 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_name_to_value(char *name, t_ms *ms);
char	*var_expand(char *str, int *j, t_ms *ms);
void	add_var_to_new(char **new, char *str, int *i, t_ms *ms);

char	*var_getter(t_ms *ms, char *str, int *j, int i)
{
	char	*var_value;
	char	*var_name;

	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		(*j)++;
	}	
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	var_value = var_name_to_value(var_name, ms);
	return (free(var_name), var_value);
}

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
char	*var_expand(char *str, int *j, t_ms *ms)
{
	int		i;

	if (!str || (str[0] != '$' && str[0] != '~'))
		return (ft_strdup(str));
	i = 1;
	(*j)++;
	if (str[0] == '~')
		return (expand_path(str, ms));
	if (str[i] && str[i] == '?')
	{
		if (!sig_comp(-1))
			return (ft_itoa((unsigned char)(128 + g_sig)));
		g_sig = -1;
		return (ft_itoa(ms->retval));
	}
	if (str[i] && str[i] == '$')
		return (ft_get_pid());
	return (var_getter(ms, str, j, i));
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

void	add_var_to_new(char **new, char *str, int *i, t_ms *ms)
{
	char	*tmp;
	char	*var;

	var = var_expand(str + *i, i, ms);
	if (!var)
	{
		perror("malloc");
		return ;
	}
	tmp = *new;
	*new = ft_strjoin(*new, var);
	free(tmp);
	free(var);
	if (str[*i])
		(*i)++;
}

// TODO recoder get pid
/** ft_get_pid - 
 * 
 * Return : the PID
*/
char	*ft_get_pid(void)
{
	int		fd;
	char	str[12];

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, str, 11) == -1)
		return (close(fd), NULL);
	close(fd);
	str[11] = '\0';
	return (ft_itoa(ft_atoi(str)));
}
