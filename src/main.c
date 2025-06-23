/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/22 12:50:38 by tcoeffet         ###   ########.fr       */
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
	tcsetattr(ms->ms_stdin, TCSADRAIN, ms->term);
	return (ret);
}

int	ms_exec(t_ms *ms)
{
	exec_init(ms);
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

	(void) ac, (void) av;
	ms = init_ms_struct(env);
	if (!ms)
		return (perror("malloc"), ms_full_clean(ms), 1);
	retval = 0;
	signal_listener();
	while (!ms->exit)
	{
		reset_ms_struct(ms);
		ms->retval = retval;
		input = readline(ms->prompt);
		if (input && *input)
			add_history(input);
		ms->token = parse(input, ms);
		if (ms->token)
		{
			retval = ms_exec(ms);
			ms_cleaner(ms);
		}
	}
	ms_full_clean(ms);
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

//DISPLAY ART

/* void	display_art(void)
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
} */