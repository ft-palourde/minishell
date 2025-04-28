/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:16 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/28 10:22:26 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_resort(char **env, int pos)
{
	int	i;

	i = pos;
	free(env[pos]);
	while (env[i + 1])
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = 0;
}

int	unset(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i] && !ft_strncmp(env[i], var, len))
		i++;
	delete_resort(env, i);
	return (0);
}

int	bi_unset(char **env, char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		unset(env, arg[i]);
		i++;
	}
	return (0);
}
