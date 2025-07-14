/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/14 12:57:31 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_getter(t_ms *ms, char *str, int *j, int i);
char	*var_expand(char *str, int *j, t_ms *ms);
char	*var_name_to_value(char *name, t_ms *ms);
void	add_var_to_new(char **new, char *str, int *i, t_ms *ms);
char	*ft_get_pid(void);

/**
 * @brief var_getter - Retrieves the value of an environment variable.
 * 
 * @param ms The minishell structure containing environment variables.
 * @param str The string containing the variable to expand (e.g., "$HOME").
 * @param j A pointer to the current index in the string (will be updated).
 * @param i The starting index after the '$' character (usually 1).
 * 
 * This function extracts the variable name from the given string,
 * starting from index `i` and collecting alphanumeric characters
 * and underscores (following POSIX rules for variable names).
 * 
 * If the character after '$' is a digit, it treats it as a special
 * variable (e.g., "$1") and retrieves its value accordingly.
 * 
 * The function then uses `var_name_to_value` to look up the variable's value.
 * 
 * @returns A newly allocated string containing the variable's value,
 * or an empty string if the variable does not exist. Returns NULL in
 * case of memory allocation failure.
 */
char	*var_getter(t_ms *ms, char *str, int *j, int i)
{
	char	*var_value;
	char	*var_name;

	if (ft_isdigit(str[i]))
	{
		(*j)++;
		var_value = var_name_to_value(NULL, ms);
		return (var_value);
	}
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

/**
 * @brief Expand a variable or special character in the string.
 *
 * Supports environment variables, `$?` (exit code), `$$` (PID), and `~` (home).
 *
 * @param str The string to expand (starting at '$' or '~').
 * @param j Pointer to cursor position in the original string (updated).
 * @param ms The minishell structure.
 * @return A newly allocated string containing the expanded value.
 */
char	*var_expand(char *str, int *j, t_ms *ms)
{
	int		i;

	if (!str || (str[0] != '$' && str[0] != '~'))
		return (ft_strdup(str));
	i = 1;
	(*j)++;
	if (str[0] == '~')
		return (expand_path(str, ms, (*j) == 1));
	if (!str[i] || is_space(str[i]))
		return (ft_strdup(str));
	if (str[i] && str[i] == '?')
	{
		(*j)++;
		if (!sig_comp(-1))
			return (ft_itoa((unsigned char)(128 + g_sig)));
		g_sig = -1;
		return (ft_itoa(ms->retval));
	}
	if (str[i] && str[i] == '$')
	{
		(*j)++;
		return (ft_get_pid());
	}
	return (var_getter(ms, str, j, i));
}

/**
 * @brief Get the value of a variable from its name.
 *
 * Searches the environment for the given variable name and returns its value.
 *
 * @param name The name of the variable (can be NULL for special cases).
 * @param ms The minishell structure containing the environment.
 * @return A newly allocated string with the variable value, or NULL on error.
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
			return (perror("minishell"), NULL);
	}
	else
		return (ft_strdup(""));
	return (value);
}

/**
 * @brief Append an expanded variable to the resulting string.
 *
 * Expands the variable at the current position and appends it to *new.
 *
 * @param new Pointer to the resulting string (modified).
 * @param str The string containing variables to expand.
 * @param i Pointer to cursor position in str (updated).
 * @param ms The minishell structure.
 */
void	add_var_to_new(char **new, char *str, int *i, t_ms *ms)
{
	char	*tmp;
	char	*var;

	var = var_expand(str + *i, i, ms);
	if (!var)
	{
		perror("minishell");
		return ;
	}
	tmp = *new;
	*new = ft_strjoin(*new, var);
	free(tmp);
	free(var);
}

/**
 * @brief Get the current process PID as a string.
 *
 * Reads /proc/self/stat to retrieve the PID.
 *
 * @return A newly allocated string with the PID, or NULL on error.
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
