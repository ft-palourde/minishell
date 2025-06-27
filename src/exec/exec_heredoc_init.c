/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:36:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/25 16:01:54 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

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
/* 

macros de lib wait :
WIFEXITED == si termine correctement
WEXITSTATUS == code de retour 
WIFSIGNALED == interrompu par signal
WTERMSIG == retourne le signal le cas echeant
*/
unsigned char wait_child(pid_t cpid)
{
	int	status;
	pid_t	retval;
	(void)cpid;
	ft_putstr_fd("\n1", 2);
	// printf("hoyoyoyoyoyo");
	// waitpid(cpid, &status, 0);
	while (1)
	{
		retval = wait(&status);
		if 	(retval == -1)
			break ;
	}
	ft_putstr_fd("\n2", 2);
	// ft_putstr_fd("pid = %d\n", retval);
	// printf("glob = %d\n", g_sig);
	if (WIFEXITED(status))
	{
		// ft_putstr_fd("toto1", 2);
		return (WEXITSTATUS(status));
	}
	ft_putstr_fd("\n3", 2);
	if (WIFSIGNALED(status))
	{
		// ft_putstr_fd("toto2", 2);
		g_sig = WTERMSIG(status);
		return ((unsigned char)(128 + g_sig));
	}
	ft_putstr_fd("\n4", 2);
	if (WIFSTOPPED(status))
	{
		// ft_putstr_fd("toto3", 2);
		return (WSTOPSIG(status));
	}
	// printf("yeyeyeyeye");
	return (0);
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
	pid_t	new;
	unsigned char	retval;
	// int		saved_fd;
	// int	i;

	g_sig = 0;
	expand = check_lim(&lim, ft_strlen(lim));
	new = fork();
	if (new == -1)
		perror("fork");
	// saved_fd = dup(ms->ms_stdin);
	// set_child_sig_handler();
	// rl_catch_signals = 0;
	if (new == 0)
	{
		// set_child_sig_handler();
		reset_dlt_sig_behaviour();
		// rl_catch_signals = 0;
		while (1 && expand != -1)
		{
			line = readline("> ");
			if (!line || (!ft_strncmp(line, lim, ft_strlen(lim)) && ft_strlen(line) == ft_strlen(lim)))
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
		close(pfd[0]);
		close(pfd[1]);
		close(3);
		close(4);
		clean_fds(ms->fd);
		clean_pfds(ms->pfd);
		// i = 3;
		// while (ms->fd && ms->fd[i] && i <= 1023)
		// {
		// 	close(i);
		// 	i++;
		// }
		// clean_fds(ms->fd);
		// clean_pfds(ms->pfd);
		exit(g_sig);
	}
	else
	{
		// close(saved_fd);
		retval = wait_child(new);
		ft_putstr_fd("i'm back in the game bitches", 2);
		// printf("retval == %d", retval);
		// ft_putstr_fd("back to parent\n", 2);
		// signal(SIGINT, &handle_sigint);
		// ft_putstr_fd("iojegrjoigerjiorgejoi", 2);
		// dup2(saved_fd, ms->ms_stdin);
		// printf("guess who's back back again");
/* 		i = 3;
		while (ms->fd && ms->fd[i] && i <= 1023)
		{
			printf("a");
			close(i);
			i++;
		} */
		// ms_cleaner(ms);
		// clean_fds(ms->fd);
		// clean_pfds(ms->pfd);
		clean_fds(ms->fd);
		// close(3);
		// close(4);
		clean_pfds(ms->pfd);
		signal(SIGINT, &handle_sigint);
		if (retval || g_sig == SIGINT)
		{
			// ft_putstr_fd("hophophop", 2);
			ms->retval = 130;
			return (1);
		}
		// ms_cleaner(ms);
	}
	return (expand == -1);
}



/* int	fill_new_hd(t_ms *ms, int *pfd, char *lim)
{
	char				*line;
	int					expand;
	char				*expanded;

	expand = check_lim(&lim, ft_strlen(lim));
	signal(SIGINT, handle_sigint_hd);
	while (1 && expand != -1)
	{
		line = readline("> ");
		if (!line || g_sig)
		{
			free(line);
			g_sig = 0;
			return (1);
		}
		if (!ft_strncmp(line, lim, ft_strlen(lim))
			&& ft_strlen(line) == ft_strlen(lim))
		{
			free(line);
			break ;
		}
		if (expand)
		{
			expanded = hd_expand(ms, line);
			free(line);
			if (!expanded)
				return (1);
			line = expanded;
		}
		ft_putstr_fd(line, pfd[1]);
		write(pfd[1], "\n", 1);
		free(line);
	}
	signal(SIGINT, &handle_sigint);
	return (0);
} */

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
	if (g_sig)
	// g_sig = 0;
	ms_signal_listener();
	close(pfd[1]);
	if (ret)
		return (close(pfd[0]), free(pfd), 1);
	if (add_fd(pfd[0], ms) || add_pfd(pfd, ms))
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
