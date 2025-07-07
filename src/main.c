/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/04 17:07:08 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	wait_all(t_ms *ms)
{
	int				i;
	unsigned char	ret;
	int				stat;

	ret = 0;
	i = 0;
	stat = 0;
	signal(SIGINT, &display_nl);
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

	err = exec_init(ms);
	if (err)
		return (130);
	build_tree(ms);
	if (!ms->tree)
		return (0);
	exec_tree(ms->tree, ms);
	return (wait_all(ms));
}

int	reset_ms_struct(t_ms *ms)
{
	ms->exit = -1;
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

void	minishell_loop(t_ms *ms, int *retval)
{
	char	*input;

	while (ms->exit == -1)
	{
		ms_signal_listener();
		reset_ms_struct(ms);
		input = readline(ms->prompt);
		if (!input)
		{
			bi_exit(ms, NULL);
			return ;
		}
		if (input && *input)
			add_history(input);
		ms->token = parse(input, ms);
		if (ms->token)
		{
			*retval = ms_exec(ms);
			ms_cleaner(ms);
		}
		ms->retval = *retval;
		g_sig = -1;
	}
}

int	main(int ac, char **av, char **env)
{
	t_ms	*ms;
	int		retval;

	g_sig = -1;
	(void)ac, (void)av;
	ms = init_ms_struct(env);
	if (!ms)
		return (perror("malloc"), ms_full_clean(ms), 1);
	retval = 0;
	minishell_loop(ms, &retval);
	if (ms->exit != -1)
		retval = ms->exit;
	ms_full_clean(ms);
	ft_putendl_fd("exit", 1);
	return (retval);
}
