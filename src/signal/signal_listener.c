/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_listener.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:01:09 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/08 13:38:48 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_signal_listener(void);

/** ms_signal_listener - On a signal reception, trigger the associated function.
 * SIGQUIT (ctrl + backslash) does nothing :
 * SIG_IGN is used to ignore this signal.
 * The other sig handled is SIGINT.
 * Each signal above has its own associated function called with signal(). 
 * https://www.gnu.org/software/libc/manual/html_node/Basic-Signal-Handling.html
 * 
 * Return : void.
*/
void	ms_signal_listener(void)
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/** sig_ignore - Ignores the behavior of SIGINT and SIGQUIT
 * 
 * Overwrite signal handler to NULL for SIGINT and SIGQUIT.
 * 
 * Return : void.
*/
void	reset_dlt_sig_behavior(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/** set_hd_sig_behavior - Changes SIGINT and SIGQUIT behavior in fork
 * 
 * SIGQUIT behavior reset to default.
 * 
 * Return : void.
*/
void	set_hd_sig_behavior(void)
{
	signal(SIGINT, &handle_sigint_hd);
	signal(SIGQUIT, SIG_DFL);
}
