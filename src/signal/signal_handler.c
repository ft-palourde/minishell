/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 09:49:09 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/25 16:47:42 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig);
int		sig_comp(int sig);

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
	int	redisplay;

	redisplay = 0;
	if (g_sig == -1)
		redisplay = 1;
	g_sig = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	// if (redisplay)
	write(1, "\n", 1);
	rl_redisplay();
	// close(STDIN_FILENO);
	return ;
}

/** handle_sigint_hd - Interrupt while heredoc filling, then cut the execution.
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
 * Close fd 0 opened with dup in parent function.
 * Returns : void.
 */
void	handle_sigint_hd(int sig)
{
	g_sig = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	close(STDIN_FILENO);
	return ;
}

/** sig_comp - Compare global variable with specified signal.
 * 
 *  @sig: int sig code to be compared with global g_sig.
 *  
 * Returns : 1 if true, 0 otherwise.
 */
int	sig_comp(int sig)
{
	if (sig == g_sig)
		return (1);
	return (0);
}
