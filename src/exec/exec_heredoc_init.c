/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:36:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:32:36 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

/** check_lim - check the content of the limiter
 * @lim: the limiter given in input
 * @len: ft_strlen(lim)
 * 
 * Checks if the limiter is simple quoted to know if its expand is required.
 * also replace the limiter with its simple quote trimed if needed
 * 
 * Returns:
 * -1 on malloc error
 * 1 if not simple quoted
 * 0 else
 */
int	check_lim(char	**lim, int len)
{
	int	expand;

	expand = 1;
	if (*lim[0] == '\'')
		expand--;
	if (is_quote(*lim[0]))
	{
		free(*lim);
		*lim = ft_strndup(*lim + 1, len - 2);
		if (!*lim)
			return (perror("malloc"), -1);
	}
	return (expand);
}

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
int	fill_new_hd(t_ms *ms, int *pfd, char *lim)
{
	char	*line;
	int		expand;

	expand = check_lim(&lim, ft_strlen(lim));
	signal(SIGINT, handle_sigint_hd);
	while (1 && expand != -1)
	{
		dup2(ms->ms_stdin, 0);
		line = readline("> ");
		if (!line || sig_comp(SIGINT))
			return (1);
		if (!ft_strncmp(line, lim, ft_strlen(lim)))
			break ;
		if (expand)
		{
			line = hd_expand(ms, line);
			if (!line)
				return (1);
		}
		ft_putstr_fd(line, pfd[1]);
		write(pfd[1], "\n", 1);
		free(line);
	}
	return (expand == -1);
}

/** add_new_hd
 * @token: the t_token of T_HEREDOC type
 * @ms: the minishell struct
 * 
 * create the pipe needed to get the heredoc content,
 * call the user for its content,
 * then add the new pfd to ms->pfd to close and free it properly
 *
 * Returns: 1 on malloc or pipe error, 0 else
 */
int	add_new_hd(t_ms *ms, t_token *token)
{
	int		*pfd;
	int		ret;

	pfd = ft_calloc(2, sizeof(int));
	if (!pfd)
		return (0);
	if (pipe(pfd) == -1)
		return (perror("pipe"), 1);
	token->data->rd->heredoc->fd = pfd;
	ret = fill_new_hd(ms, pfd, token->data->rd->heredoc->lim);
	g_sig = 0;
	signal_listener();
	close(pfd[1]);
	if (ret)
		return (close(pfd[0]), free(pfd), 1);
	if (add_fd(pfd[0], ms))
		return (1);
	return (0);
}

/** get_heredocs_pfd - get the content of all heredocs
 * @ms: the minishell struct
 * 
 * checks all the tokens to see if they are HEREDOCS
 * to initialize them
 *
 * Returns: 1 on malloc or pipe error, 0 else
 */
int	get_heredocs_pfd(t_ms *ms)
{
	t_token	*cursor;

	cursor = ms->token;
	while (cursor)
	{
		if (cursor->type == T_HEREDOC)
			if (add_new_hd(ms, cursor))
				return (1);
		cursor = cursor->next;
	}
	return (0);
}
