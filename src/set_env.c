/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:46:02 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/18 15:12:02 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*nfree(char **tofree, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tofree[n]);
		i++;
	}
	free(tofree);
	return (0);
}

int	get_env_len(char **env)
{
	int	i;
	int	need_lvl;

	need_lvl = 1;
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "SHLVL=", 6))
			need_lvl = 0;
		i++;
	}
	return (i + need_lvl);
}

char	**set_default_env(void)
{
	char	**new;

	new = ft_calloc(4, sizeof(char *));
	if (!new)
		return (0);
	new[0] = ft_strdup("PWD=/home/tcoeffet\n");
	if (!new[0])
		return (free(new), NULL);
	new[1] = ft_strdup("SHLVL=1\n");
	if (!new[1])
		return (nfree(new, 1));
	new[2] = ft_strdup("_=/usr/bin/env\n");
}

void	*change_shlvl(char **env)
{
	int		i;
	int		j;
	char	*newlvl;

	i = 0;
	j = 0;
	while (ft_strncmp(env[i], "SHLVL=", 6) && env[i])
		i++;
	if (env[i])
	{
		while (env[i][j] != '=')
			j++;
		newlvl = ft_itoa(ft_atoi(&env[i][j]));
		if (!newlvl)
			return (nfree(env, get_env_len(env)));
		free(env[i]);
		env[i] = ft_strjoin("SHLVL=", newlvl);
		if (!env[i])
			return (free(newlvl), nfree(env, get_env_len(env)));
	}
	else
		env[i] = ft_strdup("SHLVL=1");
	return (i);
}

char	**set_env(char **env)
{
	int		i;
	int		lvl;
	char	**new;
	char	*tmp;

	i = -1;
	if (!env)
		return (set_default_env());
	new = ft_calloc(get_env_len(env), sizeof(char *));
	if (!new)
		return (0);
	while (env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (nfree(new, i));
	}
	lvl = change_shlvl(new);
	if (!new)
		return (nfree(new, i - 1));
	tmp = ft_strjoin(new[lvl], "\n");
	if (!tmp)
		return (NULL);
	return (free(new[lvl]), (new[lvl] = tmp), new);
}

//compacter pour la norme :')