/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/15 12:48:32 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/** wait all
 * @ms: the minishell struct
 * 
 * wait for all the process forked to end and get their return values or signal.
 *
 * Returns: the return value of the last process
 */
int	wait_all(t_ms *ms)
{
	int				i;
	unsigned char	ret;
	int				stat;

	ret = 0;
	i = 0;
	stat = 0;
	if (!ms->pid)
		return (ms->retval);
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
	if (ms->open_failed == -1)
		return (1);
	return ((int) ret);
}

/** ms_exec
 * @ms: the minishell struct
 * 
 * call exec_init to get the content of the heredocs and sort the token list
 * in order to build the tree before executing all the commands of the input.
 *
 * Returns: the return value of the last executed command
 */
int	ms_exec(t_ms *ms)
{
	int	sigint;

	sigint = exec_init(ms);
	if (sigint)
		return (130);
	build_tree(ms);
	if (!ms->tree)
		return (0);
	exec_tree(ms->tree, ms);
	return (wait_all(ms));
}

/** reset_ms_struct
 * @ms: the minishell struct
 * 
 * reset all the variables of the ms struct to their default value
 *
 * Returns: void;
 */
void	reset_ms_struct(t_ms *ms)
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
}

/** minishell_loop
 * @ms: the minishell struct
 * @retval: a pointer to the return value variable
 * 
 * the main loop of the program, getting the input of the user
 * and then executing everything before setting the last return value
 * and then cleaning up
 *
 * Returns: void
 */
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
		ms->token = parse(input);
		if (ms->token)
		{
			*retval = ms_exec(ms);
			ms_cleaner(ms);
		}
		ms->retval = *retval;
		g_sig = -1;
	}
}

/** main
 * @ac: count of arguments received
 * @av: an array of strings containing the arguments of the program
 * @env: the environnement given to the program
 * 
 * initialize the main minishell struct containing all the datas for
 * the program to work properly, then call for the main loop.
 * When the programm receive exit as an input or a ctrl+d signal, cleans
 * everything and display exit before quitting.
 *
 * Returns: the return value of the last cmd executed or of the last signal
 */
int	main(int ac, char **av, char **env)
{
	t_ms	*ms;
	int		retval;

	g_sig = -1;
	(void)ac, (void)av;
	ms = init_ms_struct(env);
	if (!ms)
		return (perror("minishell"), ms_full_clean(ms), 1);
	retval = 0;
	minishell_loop(ms, &retval);
	if (ms->exit != -1)
		retval = ms->exit;
	ms_full_clean(ms);
	ft_putendl_fd("exit", 2);
	return (retval);
}
