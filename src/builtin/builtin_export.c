/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:11 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/15 14:43:51 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
}

int	display_sort(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
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
	print_export(env);
	reverse_cascade_free(env, split_len(env));
	return (0);
}

char	*check_var(char *var)
{
	int		i;
	char	*tmp;

	if (!var)
		return (NULL);
	tmp = 0;
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != '=')
	{
		tmp = var;
		var = ft_strjoin(var, "=");
		if (tmp)
			free(tmp);
		if (!var)
			return (perror("malloc"), NULL);
	}
	if (!i || !var[i])
		return (NULL);
	return (var);
}

static char	**export(char **env, char *var)
{
	int		env_len;
	int		i;
	char	**new_env;

	var = check_var(var);
	if (!var)
		return (env);
	env_len = split_len(env);
	new_env = ft_calloc(env_len + 2, sizeof(char *));
	if (!new_env)
		return (perror("malloc"), env);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (perror ("malloc"), reverse_cascade_free(new_env, i), env);
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		return (reverse_cascade_free(new_env, i), perror("malloc"), env);
	reverse_cascade_free(env, i - 1);
	return (new_env);
}

int	bi_export(char ***env, char **arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
	{
		display_sort(set_env(*env, 1));
		return (0);
	}
	while (arg[i])
	{
		unset(*env, arg[i]);
		*env = export(*env, arg[i]);
		i++;
	}
	return (0);
}
