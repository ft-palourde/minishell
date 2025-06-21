/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:46:02 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/17 15:30:04 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_shlvl_pos(char **env)
{
	int	i;
	int	need_lvl;

	need_lvl = 1;
	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "SHLVL=", 5))
			need_lvl = 0;
		i++;
	}
	return (i + need_lvl);
}

char	**set_default_env(void)
{
	char	**new;
	char	*pwd;

	pwd = ft_get_pwd(1);
	if (!pwd)
		return (0);
	new = ft_calloc(4, sizeof(char *));
	if (!new)
		return (0);
	new[0] = pwd;
	if (!new[0])
		return (free(new), NULL);
	new[1] = ft_strdup("SHLVL=1");
	if (!new[1])
		return (reverse_cascade_free(new, 1));
	new[2] = ft_strdup("_=/usr/bin/env");
	return (new);
}

char	*check_newlvl(char *str)
{
	int		num;
	char	*ret;

	num = ft_atoi(str) + 1;
	ret = ft_itoa(num);
	if (!ret)
		return (0);
	if (num < 0)
		return (ft_strdup("0"));
	else if (num > 1000)
	{
		write (2, "warning: shell level ", 22);
		write (2, ret, ft_strlen(ret));
		write (2, " too high, resetting to 1\n", 27);
		free(ret);
		return (ft_strdup("1"));
	}
	else
		return (ret);
}

int	change_shlvl(char **env)
{
	int		i;
	int		j;
	char	*newlvl;

	i = 0;
	j = 0;
	while (env[i] && ft_strncmp(env[i], "SHLVL=", 6))
		i++;
	if (env[i])
	{
		while (env[i][j] != '=')
			j++;
		newlvl = ft_itoa(ft_atoi(&env[i][j + 1]) + 1);
		if (!newlvl)
			return (reverse_cascade_free(env, get_shlvl_pos(env)), -1);
		free(env[i]);
		env[i] = ft_strjoin("SHLVL=", newlvl);
		free(newlvl);
		if (!env[i])
			return (reverse_cascade_free(env, get_shlvl_pos(env)), -1);
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

	i = -1;
	if (!env || !env[0])
		return (set_default_env());
	new = ft_calloc(get_shlvl_pos(env) + 1, sizeof(char *));
	if (!new)
		return (0);
	while (env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (reverse_cascade_free(new, i));
	}
	lvl = change_shlvl(new);
	if (!new || lvl == -1)
		return (reverse_cascade_free(new, i - 1));
	return (new);
}

/* mini main de test

int main(int ac, char **av)
{
	char	**env;
	int		i;

	env = set_env(&av[1], ac - 1);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	reverse_cascade_free(env, i);
	return (0);
} */