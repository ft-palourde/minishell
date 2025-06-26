/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:01:09 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/23 10:01:09 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_listener(void);

/** signal_listener - On a signal reception, trigger the associated function.
 * SIGQUIT (ctrl + backslash) does nothing :
 * SIG_IGN is used to ignore this signal.
 * The other sig handled is SIGINT.
 * Each signal above has its own associated function called with signal(). 
 * https://www.gnu.org/software/libc/manual/html_node/Basic-Signal-Handling.html
 * 
 * Return : void.
*/
void	signal_listener(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);
	return ;
}

/** sig_ignore - Ignores the behavior of SIGINT and SIGQUIT
 * 
 * Overwrite signal handler to NULL for SIGINT and SIGQUIT.
 * 
 * Return : void.
*/
void	sig_ignore(void)
{
	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
}

void	reset_dfl_sig(void)
{
	// signal(SIGQUIT, SIG_DFL);??
	signal(SIGINT, SIG_DFL);
}
