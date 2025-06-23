/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:16 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 19:06:14 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** delete_resort - delete the variable and sort back the env
 * @env: ms->env
 * @pos: the position of the variable to remove in the environnement
 * 
 * free the variable and then put its address at the end of the array
 * after the null byte and set it to 0
 *
 * Returns: 1 if variable is not found, 0 else
 */
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

/** unset - delete a variable
 * @env: ms->env
 * @var: the variable name
 * 
 * search for the variable to remove
 *
 * Returns: 1 if variable is not found, 0 else
 */
int	unset(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i] && ft_strncmp(env[i], var, len))
		i++;
	if (!env[i])
		return (1);
	delete_resort(env, i);
	return (0);
}

/** bi_unset - Builtin unset
 * @env: ms->env
 * @arg: arguments given in input
 * 
 * removes variables from the environement
 *
 * Returns: 0
 */
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
