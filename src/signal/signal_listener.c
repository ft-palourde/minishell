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

//sigint, sigquit

//SIG_IGN permeet d'ignorer un signal
// https://www.gnu.org/software/libc/manual/html_node/Basic-Signal-Handling.html
void	signal_listener(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	signal(SIGABRT, &handle_sigabort);
	signal(SIGSEGV, &handle_sigsegv);
	return ;
}
/* 
la fonction handle pointee en param de signal ne peut prendre void en argument
*/
