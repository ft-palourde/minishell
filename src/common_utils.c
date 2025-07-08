/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:46:01 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/04 11:28:50 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** display_nl
 * @sig: the signal received by signal()
 * 
 * a function to only display a newline when a signal is received by signal() 
 *
 * Returns: void
 */
void	display_nl(int sig)
{
	(void) sig;
	write(STDIN_FILENO, "\n", 1);
}

/** free_split
 * @split: an array of strings null terminated
 * 
 * free all the content of an array of strings allocd with ft_split()
 *
 * Returns: void
 */
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/** split_len
 * @split: an array of strings null terminated
 * 
 * count the number of strings in the array
 *
 * Returns: the number of strings in the array
 */
int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}
