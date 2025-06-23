/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:06 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:38:08 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** is_set
 * @str: the variable line
 * 
 * checks if the variable given is set and should be displayed
 *
 * Returns: 1 if yes, 0 else
 */
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

/** bi_env - Builtin env
 * @env: ms->env
 * 
 * displays all the environnement variables that are set
 * (with a key AND a content)
 *
 * Returns: 0
 */
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
