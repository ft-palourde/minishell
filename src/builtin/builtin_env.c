/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:06 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/22 17:58:35 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	is_set(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '=' && ft_isprint(*(str + i + 1)))
			return (1);
		i++;
	}
	return (0);
}

int	bi_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (is_set(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
