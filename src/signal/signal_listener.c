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
 * The other sig handled are SIGABRT, SIGSEGV, SIGINT.
 * Each signal above has its own associated function called with signal(). 
 * https://www.gnu.org/software/libc/manual/html_node/Basic-Signal-Handling.html
*/
void	signal_listener(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGABRT, &handle_sigabort);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGINT, &handle_sigint);
	return ;
}
