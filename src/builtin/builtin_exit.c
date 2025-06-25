/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:08 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:39:29 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** bi_exit - exit the shell
 * @ms: minishell struct
 * 
 * sets ms->exit to 1 to stop calling cmds in main()
 * 
 * returns : 0
 */
int	bi_exit(t_ms *ms)
{
	ms->exit = 1;
	return (0);
}
