/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_init2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:27:45 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 18:37:45 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			fill_new_hd(t_ms *ms, int *fd, char *lim, int expand);
int				check_lim(char	*lim);
void			abort_heredoc(t_ms *ms, int *fd);

/** fill_new_hd - get heredoc content
 * @token: the t_token of T_HEREDOC type
 * @ms: the minishell struct
 * @pfd: the int[2] array created with pipe
 * @lim: the limiter of the current heredoc
 * 
 * ask the user to fill the heredoc with readline, add all the content
 * to the pfd and handle its expand until the input is the limiter.
 *
 * Returns: 1 on malloc error, 0 else
 */
void	fill_new_hd(t_ms *ms, int *fd, char *lim, int expand)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || g_sig == SIGINT)
		{
			abort_heredoc(ms, fd);
			exit(130);
		}
		if (!ft_strncmp(line, lim, ft_strlen(lim))
			&& ft_strlen(line) == ft_strlen(lim))
			break ;
		if (expand)
		{
			expanded = hd_expand(ms, line);
			free(line);
			line = expanded;
			if (!line)
				break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
}

/** check_lim - check the content of the limiter
 * @lim: the limiter given in input
 * 
 * Checks if the limiter is simple quoted to know if its expand is required.
 * also replace the limiter with its simple quote trimed if needed
 * 
 * Returns:
 * 1 if not simple quoted
 * 0 else
 */
int	check_lim(char	*lim)
{
	int		expand;
	int		i;
	char	quote;

	i = 0;
	expand = 1;
	if (lim[0] == '\'')
		expand--;
	if (is_quote(lim[0]))
	{
		quote = lim[0];
		while (lim[i] && lim[i + 1] && lim[i + 1] != quote)
		{
			lim[i] = lim[i + 1];
			i++;
		}
		if (i)
			lim[i] = '\0';
	}
	return (expand);
}

/** @brief abort_heredoc - On SIGINT, abort the heredoc process.
 * @param ms: the minishell struct
 * @param fd_out: the fd array to close.
 */
void	abort_heredoc(t_ms *ms, int *fd_out)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	close(fd_out[0]);
	close(fd_out[1]);
	clean_fds(ms->fd);
	clean_pfds(ms->pfd);
	close(ms->ms_stdin);
	close(ms->ms_stdout);
	ms_full_clean(ms);
}
