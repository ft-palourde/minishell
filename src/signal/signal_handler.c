/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:49:09 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/23 09:49:09 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig);
void	handle_sigabort(int sig);
void	handle_sigsegv(int sig);

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	//clear input
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	handle_sigabort(int sig)
{
	(void)sig;
	write(1, "Abort\n", 6);
}

void	handle_sigsegv(int sig)
{
	(void)sig;
	write(2, "Segmentation fault\n", 19);
}
