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
void	handle_sigquit(int sig);
void	handle_sigabort(int sig);
void	handle_sigsegv(int sig);

void	handle_sigint(int sig)
{
	(void)sig;
	return ;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	return ;
}

void	handle_sigabort(int sig)
{
	(void)sig;
	return ;
}

void	handle_sigsegv(int sig)
{
	(void)sig;
	return ;
}
