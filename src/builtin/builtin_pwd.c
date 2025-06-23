/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:13 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 19:01:08 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** ft_get_pwd - pwd but as a string
 * @prefix: a bool to know if the key of the variable is needed
 * 
 * create a string which contains the value of pwd with or without the prefix
 * 'PWD='
 * 
 * Returns: mallocd string or NULL on malloc fail
 */
char	*ft_get_pwd(int prefix)
{
	char	*pwd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	pwd = 0;
	if (!tmp)
		return (perror("malloc"), NULL);
	if (prefix)
	{
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		if (!pwd)
			return (perror("malloc"), NULL);
	}
	if (!pwd)
		return (0);
	return (pwd);
}

/** bi_pwd - Built-in pwd
 * 
 * display the present working directory
 *
 * Returns: 1 on getcwd fail, 0 else
 */
int	bi_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("malloc"), 1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
