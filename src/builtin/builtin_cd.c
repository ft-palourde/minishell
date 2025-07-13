/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:00 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/13 18:09:55 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** errors_cd - errors handler
 * @path: destination path given in input
 * 
 * if cd fails, display an error message on STDOUT
 *
 * Returns: 1
 */
int	errors_cd(char *path)
{
	ft_putstr_fd("cd : ", 2);
	ft_putstr_fd(path, 2);
	if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else
		ft_putstr_fd(": Failed to change directory\n", 2);
	return (1);
}

/** move_dir
 * @env: ms->env
 * @path: destination path given in input
 * 
 * moves the user to the path given or to home if no path
 *
 * Returns: 1 on error, 0 else
 */
int	move_dir(char *path, t_ms *ms)
{
	int	ret;
	int	empty;

	ret = 0;
	empty = 0;
	if (!path)
	{
		empty = 1;
		if (!var_exists(ms->env, "HOME"))
			return (ft_putendl_fd("HOME not set", 2), 1);
		path = var_name_to_value("HOME", ms);
		if (!path)
			return (0);
	}
	if (!path[0])
		return (0);
	ret = chdir((const char *)path);
	if (ret)
	{
		errors_cd(path);
		ret = 1;
	}
	if (empty)
		free(path);
	return (ret);
}

/** bi_cd - Built-in command cd
 * @env: ms->env
 * @path: destination path given in input
 * 
 * moves the user to the path given and sets the new $PWD
 *
 * Returns: 1 on error, 0 else
 */
int	bi_cd(char **env, char **args, t_ms *ms)
{
	char	*new_path;
	int		i;
	int		ret;

	i = 0;
	if (args && args[1] && args[2])
	{
		ft_putendl_fd("Minishell : cd : too many arguments", 2);
		return (1);
	}
	ret = move_dir(args[1], ms);
	if (ret)
		return (ret);
	while (env[i] && ft_strncmp("PWD=", env[i], 4))
		i++;
	if (!env[i])
		return (1);
	new_path = ft_get_pwd(1);
	if (!new_path)
		return (1);
	free(env[i]);
	env[i] = new_path;
	return (0);
}
