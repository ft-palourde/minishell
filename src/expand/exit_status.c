/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:10:47 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/25 15:53:24 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO demain

/* la fonction check exit status verifie si la cle de la variable
est un `?` seul, si oui elle renvoit la valeur numerique du dernier exit code retenu
sinon elle renvoit -1*/
int	*check_exit_status(char *var, t_ms *ms)
{
	if (var[0] != '$' && (var[1] && var[1] != '?'))
		return (-1);
	if (!var[2] || ft_isspace(var[2]))
		return (ms->retval);
	return (-1);
}
