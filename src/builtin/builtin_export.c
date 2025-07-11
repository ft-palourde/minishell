/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:11 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/09 18:58:26 by rcochran         ###   ########.fr       */
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

int	var_is_legal(char *var_name)
{
	int	i;

	i = 0;
	if (!var_name || !ft_isalpha(var_name[0]))
		return (0);
	while (var_name[i] && var_name[i] != '=')
	{
		if (!ft_isalnum(var_name[i]))
			return (0);
		i++;
	}
	return (1);
}

int	xprt_get_var_content(char *var, char **var_content)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	*var_content = ft_strdup(var + i + 1);
	if (!*var_content)
		return (perror("Minishell"), 1);
	return (0);
}

int	xprt_get_var_name(char *var, char **var_name)
{
	int	has_sign;
	int	len;

	len = 0;
	has_sign = 0;
	while (var[len])
	{
		if (var[len] == '=')
		{
			has_sign = 1;
			break ;
		}
		len++;
	}
	*var_name = ft_strndup(var, len + has_sign);
	if (!*var_name)
		return (perror("Minishell"), 1);
	return (has_sign);
}

int	is_set(char *var_name, char **env, int has_content)
{
	int	len;
	int	i;

	len = ft_strlen(var_name) - has_content;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len))
			if (env[i][len + 1] && env[i][len + 1] == '=')
				return (i);
		i++;
	}
	return (0);
}

int	xprt_replace(char *var_name, char *var_content, char **env, int i)
{
	char	*new_var;

	new_var = ft_strjoin(var_name, var_content);
	if (!new_var)
		return (perror("Minishell"), 1);
	free(env[i]);
	env[i] = new_var;
	return (0);
}

int	xprt_set(char *var_name, char *var_content, char **env, int has_content)
{
	char	**new_env;
	int		len;

	len = split_len(env) + 1;
	new_env = ft_realloc(env, len + 1);
	if (!new_env)
		return (perror("Minishell"), 1);
	

	//creer une copie de l'env avec une place en plus
	// si content : strjoin var_name et content
	// ajouter var_name a la fin
}

int	export_loop(char *arg, char ***env)
{
	int		has_content;
	int		env_index;
	char	*var_name;
	char	*var_content;

	has_content = xprt_get_var_name(arg, &var_name);
	if (!var_name)
		return (1);
	if (!var_is_legal(var_name))
		return (free(var_name), 1);
	if (has_content && xprt_get_var_content(arg, &var_content))
		return (free(var_name), 1);
	env_index = is_set(var_name, *env, has_content);
	if (env_index)
		if (has_content && xprt_replace(var_name, var_content, *env, env_index))
			return (free(var_name), free(var_content), 1);
	else
		if (xprt_set(var_name, var_content, *env, has_content))
			return (free(var_name), free(var_content), 1);
	return (free(var_name), free(var_content), 1);
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
		export_loop(arg[i], env);
		i++;
	}
	return (0);
}

/* 

export : 

while(args[i])
{
	check content
	recuperer le nom de la var
		si !legale
			out
	recuperer le contenu de la var
	check si la var est set
		si content
			je remplace
	else
		je set
		si content
			je set le content
	i++
}*/