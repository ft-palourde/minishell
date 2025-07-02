/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:36:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/01 15:38:00 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int				check_lim(char	**lim, int len);
unsigned char	wait_child(pid_t cpid);
void			abort_heredoc(t_ms *ms, int *fd);
void			fill_new_hd(t_ms *ms, t_token *token, char *lim, int expand);
int				fork_hd(t_ms *ms, t_token *token, char *lim);
int				add_new_hd(t_ms *ms, t_token *token);
int				get_heredocs_pfd(t_ms *ms);

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

int	is_lim(char *line, char *lim, t_token *token)
{
	if (!ft_strncmp(line, lim, ft_strlen(lim)) \
			&& ft_strlen(line) == ft_strlen(lim))
		return (1);
	token->data->rd->heredoc->is_empty = 0;
	return (0);
}

/* 
macros de lib wait :
WIFEXITED == si termine correctement
WEXITSTATUS == code de retour 
WIFSIGNALED == interrompu par signal
WTERMSIG == retourne le signal le cas echeant
*/
unsigned char	wait_child(pid_t cpid)
{
	int	status;

	if (waitpid(cpid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	ft_putstr_fd("toto\n", 2);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		g_sig = WTERMSIG(status);
		return (128 + g_sig);
	}
	if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (0);
}

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
void	fill_new_hd(t_ms *ms, t_token *token, char *lim, int expand)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || g_sig == SIGINT)
		{
			abort_heredoc(ms, token->data->rd->heredoc->fd);
			exit(130);
		}
		if (is_lim(line, lim, token))
			break ;
		if (expand)
		{
			expanded = hd_expand(ms, line);
			free(line);
			line = expanded;
			if (!line)
				break ;
		}
		ft_putendl_fd(line, token->data->rd->heredoc->fd[1]);
		free(line);
	}
}

int	fork_hd(t_ms *ms, t_token *token, char *lim)
{
	pid_t	child_pid;
	int		expand;
	int		status;

	g_sig = 0;
	expand = check_lim(&lim, ft_strlen(lim));
	if (expand == -1)
		return (perror("malloc"), 1);
	child_pid = fork();
	if (child_pid == -1)
		return (perror("fork"), 1);
	if (child_pid == 0)
	{//extract tout ce bloc dans un bloc handle_child()
		// set_hd_sig_behaviour();
		reset_dlt_sig_behaviour();
		close(token->data->rd->heredoc->fd[0]);
		fill_new_hd(ms, token, lim, expand);
		close(token->data->rd->heredoc->fd[1]);
		clean_fds(ms->fd);
		clean_pfds(ms->pfd);
		exit(0);
	}
	// le reste dans handle parent()
	close(token->data->rd->heredoc->fd[1]);
	if (waitpid(child_pid, &status, 0) == -1)
		return (perror("waitpid"), 1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ms->retval = 130;
		g_sig = SIGINT;
		close(token->data->rd->heredoc->fd[0]);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(token->data->rd->heredoc->fd[0]);
		return (1);
	}
	return (0);
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

	pfd = ft_calloc(2, sizeof(int));
	if (!pfd)
		return (0);
	if (pipe(pfd) == -1)
		return (perror("pipe"), 1);
	token->data->rd->heredoc->fd = pfd;
	sig_ignore();
	if (fork_hd(ms, token, token->data->rd->heredoc->lim))
	{
		write(1, "\n", 1);
		close(pfd[0]);
		close(pfd[1]);
		return (free(pfd), 1);
	}
	reset_std_dup(ms);
	ms_signal_listener();
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
