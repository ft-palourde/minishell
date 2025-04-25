/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/22 17:57:21 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	main(int ac, char **av, char **env)
{
	char	**new_env;
	int		len;

	(void) ac;
	new_env = set_env(env, 1);
	if (!new_env)
		return (0);
	len = split_len(new_env);
	printf ("env function \n");
	bi_env(new_env);
	printf("\n\npwd\n");
	bi_pwd();
	printf("\n\ncd\n");
	bi_cd(new_env, av[1]);
	printf("\n\nnew pwd\n");
	bi_pwd();
	printf("\n\nunset PWD\n");
	bi_unset(new_env, av[2]);
	bi_env(new_env);
	reverse_cascade_free(new_env, len);
	return (0);
}
