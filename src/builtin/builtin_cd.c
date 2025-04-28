/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:00 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/28 10:06:19 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errors_cd(char *path)
{
	ft_putstr_fd("cd : ", 2);
	ft_putstr_fd(path, 2);
	if (errno == ENOENT)
		ft_putstr_fd(" No suc file or directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(" Permission denied\n", 2);
	else
		ft_putstr_fd(" Failed to change directory\n", 2);
	return (1);
}

char	*get_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while (env[i] && strncmp(env[i], "HOME=", 5))
		i++;
	if (!env[i])
		return (ft_putstr_fd("cd : HOME not set\n", 2), NULL);
	home = get_var_value(env[i]);
	if (!home)
		return (perror("malloc"), NULL);
	return (home);
}

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
