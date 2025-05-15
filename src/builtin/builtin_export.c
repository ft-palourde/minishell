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
	bi_env(env);
	reverse_cascade_free(env, split_len(env));
	return (0);
}

int	is_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!i || !var[i] || var[i] != '=' || !var[i + 1])
		return (0);
	return (1);
}

static char	**export(char **env, char *var)
{
	int		env_len;
	int		i;
	char	**new_env;

	if (!is_var(var))
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
