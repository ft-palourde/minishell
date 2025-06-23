/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:00 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:30:36 by tcoeffet         ###   ########.fr       */
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
		ft_putstr_fd(" No such file or directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(" Permission denied\n", 2);
	else
		ft_putstr_fd(" Failed to change directory\n", 2);
	return (1);
}

/** bi_cd - Built-in command cd
 * @env: ms->env
 * @path: destination path given in input
 * 
 * moves the user to the path given and sets the new $PWD
 *
 * Returns: 1 on error, 0 else
 */
int	bi_cd(char **env, char *path)
{
	char	*new_path;
	int		i;
	int		ret;

	i = 0;
	if (!path)
		return (1);
	ret = chdir((const char *)path);
	if (ret)
		return (errors_cd(path));
	while (env[i] && !ft_strncmp("PWD=", env[i], 4))
		i++;
	if (!env[i])
		return (1);
	new_path = ft_get_pwd(1);
	if (!new_path)
		return (perror("malloc failed"), 1);
	free(env[i]);
	env[i] = new_path;
	return (0);
}
