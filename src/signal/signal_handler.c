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
int		sig_comp(int sig);
int		is_ctrlc(void);

int	g_sig;

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
	g_sig = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	// rl_redisplay();
	close(0);
	return ;
}

/* void	handle_sigint_hd(int sig)
{
	g_sig = sig;
	if (is_ctrlc)
	
	return ;
} */

int	sig_comp(int sig)
{
	if (sig == g_sig)
	{
		g_sig = 0;
		return (1);
	}
	return (0);
}

int	is_ctrlc(void)
{
	return (sig_comp(SIGINT));
}
