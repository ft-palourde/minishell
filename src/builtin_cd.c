/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:00 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/21 17:24:01 by tcoeffet         ###   ########.fr       */
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

int	bi_cd(char **env, char *path)
{
	int		i;
	char	*tmp;

	i = 0;
	chdir((const char *)path);
	while (env[i] && !ft_strncmp("PWD=", env[i], 4))
		i++;
	if (!env[i])
		return (1);
	tmp = ft_strreplace(env[i], path, i);
	if (!tmp)
		return (perror(malloc), 1);
	free(env[i]);
	env[i] = tmp;
	return (0);
}
