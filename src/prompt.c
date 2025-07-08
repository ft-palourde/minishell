/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:28:30 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/17 15:53:14 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define S_PR "\001\x1b[30;47;1m\002 TCoeffet & RCochran \001\033[0m\x1b[1m\002 "

/** get_pwd
 * @env: an array of strings containing the environement variables
 * 
 * get the value of the PWD variable in the env if it is set.
 * 
 * Returns: the content of $PWD, and empty string if not set,
 * or NULL on malloc fail
 */
char	*get_pwd(char **env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	while (env[i] && env[i][j])
		j++;
	if (!i || !j)
		return (ft_strdup(""));
	j--;
	while (env[i][j] != 47 && env[i][j])
		j--;
	return (ft_strdup(env[i] + j + 1));
}

/** get_prompt
 * @env: an array of strings containing the environement variables
 * 
 * build a custom prompt for readline
 * 
 * Returns: the prompt to display or null on malloc error
 */
char	*get_prompt(char **env)
{
	const char	*start = S_PR;
	char		*tmp;
	char		*prompt;

	if (!env)
		return (ft_strdup("minishell >"));
	tmp = get_pwd(env);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(start, tmp);
	free(tmp);
	if (!prompt)
		return (NULL);
	tmp = ft_strjoin(prompt, " > \001\033[0m\002");
	free(prompt);
	if (!tmp)
		return (NULL);
	prompt = tmp;
	return (prompt);
}
