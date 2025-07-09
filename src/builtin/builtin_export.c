/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:11 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:56:05 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** print_export - print sorted env
 * @env: sorted copy of ms->env
 * 
 * displays the sorted copy of ms->env on STDOUT and then free the copy
 *
 * Returns: 0
 */
int	print_export(char **env)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (env[i])
	{
		name = get_var_name(env[i]);
		if (!name)
			return (1);
		value = get_var_value(env[i]);
		if (!value)
			return (free(name), 1);
		printf("export %s=\"%s\"\n", name, value);
		free(name);
		free(value);
		i++;
	}
	reverse_cascade_free(env, split_len(env));
	return (0);
}

/** display_sort - display env in alphabetic order
 * @env: a copy of ms->env
 * 
 * sort a copy of the env and displays it on STDOUT
 *
 * Returns: 0
 */
int	display_sort(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	if (!env)
		return (1);
	while (env[j])
		j++;
	while (j > 0)
	{
		i = 0;
		while (i + 1 < j)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
			i++;
		}
		j--;
	}
	return (print_export(env));
}

/** check_var - checks if the variable is well formated
 * @var: environnement variable to set
 * 
 * checks if the variable contains an '=' sign and add it if needed
 *
 * Returns: NULL on malloc failed or the mallocd variable
 */
char	*check_var(char *var)
{
	int		i;
	char	*new_var;

	new_var = 0;
	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != '=')
	{
		new_var = ft_strjoin(var, "=");
		if (!new_var)
			return (perror("minishell"), NULL);
	}
	else
		new_var = ft_strdup(var);
	if (!i || (new_var && !new_var[i]))
		return (free(new_var), NULL);
	return (new_var);
}

/** export - add a variable
 * @env: ms->env
 * @var: environnement variable to set
 * 
 * realloc the environnement with one more string to copy the new variable to
 *
 * Returns: the new env 
 * or the old env if malloc failed or the variable cant be set
 */
static char	**export(char **env, char *var)
{
	int		env_len;
	int		i;
	char	**new_env;
	char	*new_var;

	new_var = check_var(var);
	if (!new_var)
		return (env);
	env_len = split_len(env);
	new_env = ft_calloc(env_len + 2, sizeof(char *));
	if (!new_env)
		return (perror("minishell"), env);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (perror ("malloc"), reverse_cascade_free(new_env, i), env);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	free(new_var);
	if (!new_env[i])
		return (reverse_cascade_free(new_env, i), perror("minishell"), env);
	return (reverse_cascade_free(env, i - 1), new_env);
}

/** bi_export - Builtin export
 * @env: ms->env
 * @arg: arguments given in input
 * 
 * add a new variable to the environnement or truncate it if it already exists.
 * if export is called without argument, displays all the variable in 
 * alphabetical order
 *
 * Returns: 1 on malloc failed, 0 else
 */
int	bi_export(char ***env, char **arg)
{
	int		i;
	char	*to_unset;

	i = 0;
	if (!arg || !arg[0])
	{
		if (display_sort(set_env(*env)))
			return (1);
		return (0);
	}
	while (arg[i])
	{
		if (is_var(arg[i]))
		{
			to_unset = get_var_name(arg[i]);
			unset(*env, to_unset);
			free(to_unset);
			*env = export(*env, arg[i]);
		}
		else if (var_exists(*env, arg[i]) <= 0)
			*env = export(*env, arg[i]);
		i++;
	}
	return (0);
}
