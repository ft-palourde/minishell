/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:11 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/12 17:43:51 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** print_export - print sorted env
 * @env: sorted copy of ms->env
 * 
 * displays the sorted copy of ms->env on STDOUT and then free the copy
 *
 * Returns: 0
 */
int	print_export(char **env)
{
	int		i;
	int		j;

	i = -1;
	while (env[++i])
	{
		j = 0;
		ft_putstr_fd("export ", STDOUT_FILENO);
		while (env[i][j] && env[i][j] != '=')
		{
			write(STDOUT_FILENO, &env[i][j], 1);
			j++;
		}
		if (!env[i][j])
		{
			write(STDOUT_FILENO, "\n", 1);
			continue ;
		}
		write(STDOUT_FILENO, "=\"", 2);
		while (env[i][++j])
			write(STDOUT_FILENO, &env[i][j], 1);
		write(STDOUT_FILENO, "\"\n", 2);
	}
	reverse_cascade_free(env, split_len(env));
	return (0);
}

/**
 * @brief sorts the environnement and displays it
 *
 * makes a copy of the environnement and then sorts it in alphabetical 
 * order of its variable name before displaying it in the terminal
 *
 * @param env an array of strings containing all the environnement variables
 * @return 1 if the copy failed, 0 else
 */
int	display_sort(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	if (!env)
		return (1);
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
	return (print_export(env));
}

/**
 * @brief set a new variable in the environnement
 *
 * make a copy of the environnement with an extra space,
 * then build a string to add in it and put it at the end
 *
 * @param var_name the name of the variable to expand with or without = sign
 * @param var_content the content of the variable to expand
 * @param ms The minishell structure.
 * @param has_content a boolean showing if there is a content in the argument
 * @return 1 on malloc fail, 0 else
 */
int	xprt_set(char *var_name, char *var_content, t_ms *ms, int has_content)
{
	char	*new_var;
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	new_var = xprt_build_var(var_name, var_content, has_content);
	if (!new_var)
		return (perror("Minishell"), 1);
	len = split_len(ms->env);
	new_env = ft_calloc((len + 2), sizeof(char *));
	if (!new_env)
		return (perror("Minishell"), 1);
	while (ms->env[i])
	{
		new_env[i] = ms->env[i];
		i++;
	}
	new_env[len] = new_var;
	free(ms->env);
	ms->env = new_env;
	return (0);
}

/**
 * @brief main loop to execute export with one argument
 *
 * checks if there is anything to add and if the variable already exists to
 * set it in the right way. If the variable doesnt exist, create a copy of
 * the environement with an extra space to put the variable
 *
 * @param arg the argument of export to add to the environnement
 * @param ms The minishell structure.
 * @return 1 on error, 0 else.
 */
int	xprt_loop(char *arg, t_ms *ms)
{
	int		has_content;
	int		env_index;
	char	*var_name;
	char	*var_content;

	has_content = xprt_get_var_name(arg, &var_name);
	if (!var_name)
		return (1);
	if (!var_is_legal(var_name))
		return (free(var_name), 1);
	if (has_content && xprt_get_var_content(arg, &var_content))
		return (free(var_name), 1);
	env_index = xprt_is_set(var_name, ms->env, has_content);
	if (env_index != -1)
	{
		if (has_content && xprt_replace(var_name, var_content, ms, env_index))
			return (free(var_name), 1);
	}
	else
	{
		if (xprt_set(var_name, var_content, ms, has_content))
			return (free(var_name), free(var_content), 1);
	}
	return (free(var_name), 1);
}

/** bi_export - Builtin export
 * @env: ms->env
 * @arg: arguments given in input
 * 
 * add a new variable to the environnement, it can be declared but
 * not set if there is no = sign in it.
 * If no argument is given export only displays all the variables
 * in alphabetical order
 *
 * Returns: 1 on malloc failed, 0 else
 */
int	bi_export(t_ms *ms, char **arg)
{
	int		i;

	i = 0;
	if (!arg || !arg[0])
	{
		if (display_sort(set_env(ms->env)))
			return (1);
		return (0);
	}
	while (arg[i])
	{
		xprt_loop(arg[i], ms);
		i++;
	}
	return (0);
}
