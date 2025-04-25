/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:00 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/23 14:33:55 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strreplace(char *s1, char *s2, int n)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_calloc(ft_strlen(s2) + n, sizeof(char));
	if (!new)
		return (0);
	while (i < n)
	{
		new[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new[i + n] = s2[i];
		i++;
	}
	return (new);
}

int	errors_cd(char path)
{
	ft_putstr_fd(2, "cd : ");
	ft_putstr_fd(2, path);
	if (errno == ENOENT)
		ft_putstr_fd(2, " No suc file or directory\n");
	else if (errno == EACCES)
		ft_putstr_fd(2, " Permission denied\n");
	else
		ft_putstr_fd(2, " Failed to change directory\n");
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
		return (ft_putstr_fd(2, "cd : HOME not set\n"), NULL);
	home = get_var_value(env[i]);
	if (!home)
		return (perror("malloc"), 0);
	return (home);
}

int	bi_cd(char **env, char *path)
{
	char	*new_path;
	int		i;
	int		ret;

	i = 0;
	path = expend_path(env, path);
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
