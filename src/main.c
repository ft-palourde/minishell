/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/09 18:08:29 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	wait_all(t_ms *ms)
{
	int	i;
	int	ret;
	int	stat;

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
			ret = WTERMSIG(stat);
		i++;
	}
	return (ret);
}

int	ms_exec(t_ms *ms)
{
	exec_init(ms);
	build_tree(ms);
	// debug_print_tree(ms->tree, 0);
	if (!ms->tree)
		return (0);
	exec_tree(ms->tree, ms);
	ms->retval = wait_all(ms);
	return (0);
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
	return (0);
}

void	display_art(void)
{
	int		fd;
	char	*line;

	fd = open("./assets/ms_ascii", O_RDONLY);
	if (fd == -1)
		return ;
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
		else
			break ;
	}
	close(fd);
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_ms	*ms;

	if (ac > 1 && !strncmp("-h", av[1], 2))
		display_art();
	prompt = get_prompt(env);
	ms = init_ms_struct(env);
	if (!ms)
		return (perror("malloc"), 1);
	if (!prompt)
		return (1);
	while (!ms->exit)
	{
		reset_ms_struct(ms);
		ms->token = parse(readline(prompt));
		if (ms->token)
		{
			ms_exec(ms);
			ms_cleaner(ms);
		}
	}
	ms_full_clean(ms, prompt);
	return (0);
}

// DEBUG TOKENS

/* int	main(int ac, char **av, char **env)
{
	char		*prompt;
	char		*line;
	t_token		*tokens;

	(void) env;
	(void) av;
	(void) ac;
	tokens = NULL;
	prompt = get_prompt(env);
	line = readline(prompt);
	if (*line == '\0')
		free(line);
	printf("%s", line);
	while (strncmp("EXIT", line, 5))
	{
		tokens = parse(line);
		if (!tokens)
			printf("\nParsing error\n");
		debug_display_token_args(tokens);
		line = readline(prompt);
		printf("%s", line);
	}
	free_tokens(tokens);
	free(prompt);
	return (0);
} */
