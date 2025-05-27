/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:57:03 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/27 15:05:42 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_minishistory(void);
void	add_to_minishistory(char *input, char **minishistory);
char	**clear_minishistory(void);

char	**init_minishistory(void)
{
	char	**minishistory;

	minishistory = ft_calloc(1, sizeof(char *));
	return (NULL);
}

void	add_to_minishistory(char *input, char **minishistory)
{
	return ;
}

char	**clear_minishistory(void)
{
	return (NULL);
}
