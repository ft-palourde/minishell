/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/30 11:33:38 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int	g_sig;

int	wait_all(t_ms *ms)
{
	int				i;
	unsigned char	ret;
	int				stat;

	ret = 0;
	i = 0;
	stat = 0;
	while (ms->pid && ms->pid[i])
	{
		if (ms->pid[i])
			waitpid(ms->pid[i], &stat, 0);
		if (WIFEXITED(stat))
			ret = WEXITSTATUS(stat);
		if (WIFSIGNALED(stat))
			ret = WTERMSIG(stat) + 128;
		i++;
	}
	tcsetattr(ms->ms_stdin, TCSADRAIN, ms->term);
	return ((int) ret);
}

int	ms_exec(t_ms *ms)
{
	int	err;

	// printf("ENTER ms_exec\n");
/* 	if (g_sig == SIGINT)
		return (130); */
	err = exec_init(ms);
	if (err)
		perror("malloc");
	// display_tokens(ms->token);
	build_tree(ms);
	if (!ms->tree)
		return (0);
	exec_tree(ms->tree, ms);
	return (wait_all(ms));
}

int	reset_ms_struct(t_ms *ms)
{
	ms->exit = 0;
	ms->file_in = STDIN_FILENO;
	ms->file_out = STDOUT_FILENO;
	ms->open_failed = 0;
	ms->token = 0;
	ms->tree = 0;
	ms->pid = 0;
	ms->fd = 0;
	ms->pfd = 0;
	tcgetattr(STDIN_FILENO, ms->term);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_ms	*ms;
	char	*input;
	int		retval;

	g_sig = -1;
	// rl_event_hook = &event;
	(void)ac, (void)av;
	ms = init_ms_struct(env);
	if (!ms)
		return (perror("malloc"), ms_full_clean(ms), 1);
	retval = 0;
	ms_signal_listener();
	while (!ms->exit)
	{
		reset_ms_struct(ms);
		// dup2(ms->ms_stdin, 0);
		input = readline(ms->prompt);
		// printf("INPUT: [%s]\n", input);
		if (input && *input)
			add_history(input);
		ms->token = parse(input, ms);
		if (ms->token)
		{
			retval = ms_exec(ms);
			ms_cleaner(ms);
		}
		// printf("gsig = %d\n\n", g_sig);
		if (g_sig == SIGINT)
		{
			g_sig = -1;
			ms->retval = 130;
		}
		else
			ms->retval = retval;
		g_sig = -1;
	}
	ms_full_clean(ms);
	return (0);
}
