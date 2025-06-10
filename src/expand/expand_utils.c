/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:14:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 12:09:13 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*get_home(char **env)
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
} */

// faire une fonction char	*get_var() qui reprend la logique gethome pour toute variable