/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:11:02 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/12 17:32:25 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief sets the content of the variable given as argument to export
 *
 * sets the mallocd content of the variable given as argument with or
 * without an '=' sign and returns if there was a sign or not
 *
 * @param var the string of the variable given as argument to export
 * @param var_name the address of the variable var name to set
 * @return 1 on malloc error or 0 else
 */
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

/**
 * @brief sets the name of the variable given as argument to export
 *
 * sets the mallocd name of the variable given as argument with or
 * without an '=' sign and returns if there was a sign or not
 *
 * @param var the string of the variable given as argument to export
 * @param var_name the address of the variable var name to set
 * @return 1 if there is an = sign or on malloc error or 0 else
 */
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

/**
 * @brief checks if the variable already exists int the env
 *
 * checks if the variable already exists int the env and gives its position
 *
 * @param var_name the name of the variable containing or not an = sign
 * @param env an array of strings containing all environnement variables
 * @param has_content a boolean telling if there is content to add or not
 * @return the index of the variable in the env or -1 if not found
 */
int	xprt_is_set(char *var_name, char **env, int has_content)
{
	int	len;
	int	i;

	len = ft_strlen(var_name) - has_content;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len))
			if ((env[i][len] && env[i][len] == '=') || !env[i][len])
				return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief replaces the content of a variable already existing in the env
 *
 * allocate the new variable to replace and adds it where the variable
 * was before in the env
 *
 * @param var_name the name of the variable containing or not an = sign
 * @param var_content the content of the variable
 * @param ms the minishell struct containing datas for the project
 * @param i the index of the variable in the env
 * @return 1 if malloc failed, 0 else
 */
int	xprt_replace(char *var_name, char *var_content, t_ms *ms, int i)
{
	char	*new_var;

	new_var = ft_strjoin(var_name, var_content);
	free(var_content);
	if (!new_var)
		return (perror("Minishell"), 1);
	free(ms->env[i]);
	ms->env[i] = new_var;
	return (0);
}

/**
 * @brief builds the new variable to be add in the env
 *
 * checks if the variable has a content to add or not and mallocs its string
 *
 * @param var_name the name of the variable containing or not an = sign
 * @param var_content the content of the variable
 * @param content a boolean telling if there is content to add or not
 * @return the mallocs variable to add in the env
 */
char	*xprt_build_var(char *var_name, char *var_content, int content)
{
	char	*new_var;

	if (content)
	{
		new_var = ft_strjoin(var_name, var_content);
		free(var_content);
	}
	else
		new_var = ft_strdup(var_name);
	return (new_var);
}
