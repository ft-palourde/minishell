/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:13 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/21 16:12:55 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(int prefix)
{
	char	*pwd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (0);
	if (prefix)
	{
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		if (!pwd)
			return (0);
		tmp = pwd;
	}
	pwd = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!pwd)
		return (0);
	return (pwd);
}

int	bi_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror(malloc), 1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
