/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/28 11:34:19 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**new_env;

	(void) av;
	(void) ac;
	new_env = set_env(env, 1);
	if (!new_env)
		return (0);
	bi_export(&new_env, &av[1]);
	printf("\n\n");
	bi_env(new_env);
	reverse_cascade_free(new_env, split_len(new_env));
	return (0);
}
