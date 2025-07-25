/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:36:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/08 13:38:43 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				fork_hd(t_ms *ms, int *pfd, char *lim);
int				add_new_hd(t_ms *ms, t_token *token);
int				get_heredocs_pfd(t_ms *ms);
void			handle_child(t_ms *ms, int *pfd, char *lim, int expand);

/** handle_child
 * @ms: the minishell struct
 * @pfd: int[2] the pipe opened for the heredoc
 * @lim: the limiter string for the heredoc
 * @expand: a boolean to check if the heredoc needs to expand its content
 * 
 * set the signal behaviour, then get all the content for the heredoc and
 * free and close all that needs to before exiting.
 *
 * Returns: 1 on malloc or pipe error, 0 else
 */
void	handle_child(t_ms *ms, int *pfd, char *lim, int expand)
{
	set_hd_sig_behavior();
	reset_dlt_sig_behavior();
	fill_new_hd(ms, pfd, lim, expand);
	close(pfd[0]);
	close(pfd[1]);
	ms_full_clean(ms);
}

/** wait_pid_hd
 * @ms: the minishell struct
 * @pfd: int[2] the pipe opened for the heredoc
 * @child_pid: the pid returned by fork on fork_hd
 * 
 * wait for the child receveiving the content for the heredoc
 * to finish, keep the value of the signal returned by the child
 *
 * Returns: 1 on malloc or pipe error, 0 else
 */
int	wait_pid_hd(t_ms *ms, int *pfd, int child_pid)
{
	int		status;

	if (waitpid(child_pid, &status, 0) == -1)
		return (perror("waitpid"), 1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ms->retval = 130;
		g_sig = SIGINT;
		close(pfd[0]);
		return (1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pfd[0]);
		return (1);
	}
	return (0);
}

/** fork_hd
 * @ms: the minishell struct
 * @pfd: int[2] the pipe opened for the heredoc
 * @lim: the limiter string for the heredoc
 * 
 * create a fork in order to get the content to save in the heredoc
 * while managing signals properly
 *
 * Returns: 1 on error, 0 else
 */
int	fork_hd(t_ms *ms, int *pfd, char *lim)
{
	pid_t	child_pid;
	int		expand;

	g_sig = 0;
	expand = check_lim(lim);
	if (expand == -1)
		return (perror("minishell"), 1);
	child_pid = fork();
	if (child_pid == -1)
		return (perror("minishell"), 1);
	if (child_pid == 0)
	{
		handle_child(ms, pfd, lim, expand);
		exit(0);
	}
	close(pfd[1]);
	return (wait_pid_hd(ms, pfd, child_pid));
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
		return (perror("minishell"), 1);
	token->data->rd->heredoc->fd = pfd;
	sig_ignore();
	if (fork_hd(ms, pfd, token->data->rd->heredoc->lim))
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
