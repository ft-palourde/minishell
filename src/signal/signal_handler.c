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

/** handle_sigint - Display a new line and redisplay prompt.
 * @sig: int sig code given by signal(), cannot be null or void.
 *
 * rl_replace_line() :
 * Replace the contents of rl_line_buffer with text.
 * The point and mark are preserved, if possible.
 * If clear_undo is non-zero, 
 * the undo list associated with the current line is cleared.
 * 
 * rl_on_new_line() : 
 * Tell the update functions that we have moved onto a new (empty) line,
 * usually after outputting a newline. 
 * 
 * rl_redisplay() :
 * Change what’s displayed on the screen
 * to reflect the current contents of rl_line_buffer.
 * 
 * Returns : void.
 */
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

/** handle_sigabort - Handle ABORT signal.
 * @sig: int sig code given by signal(), cannot be null or void.
 *
 * Display "Abort\n" in STDOUT
 * 
 * Returns : void.
 */
void	handle_sigabort(int sig)
{
	(void)sig;
	write(1, "Abort\n", 6);
}

/** handle_sigsegv - Handle SIGINT signal.
 * @sig: int sig code given by signal(), cannot be null or void.
 *
 * Display "Segmentation fault\n" in STDERR
 * 
 * Returns : void.
 */
void	handle_sigsegv(int sig)
{
	(void)sig;
	write(2, "Segmentation fault\n", 19);
}
