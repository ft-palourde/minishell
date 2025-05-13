/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/26 17:02:23 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_all(t_ms *ms)
{
	(void) ms;
}

void	wait_pid(t_ms *ms)
{
	int	i;
	int	ret;
	int	stat;

	ret = 0;
	i = 0;
	stat = 0;
	while (ms->pid[i])
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
	ms->tree = build_tree(ms->token);
	exec_tree(ms->tree, ms);
	wait_pid(ms);
	return (0);
}

int	main(int ac, char **av, char **env)
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
	tokens = parse(line);
	if (!tokens)
	{
		printf("\nParsing error\n");
		free(line);
		free(prompt);
		return (1);
	}
	debug_display_token_args(tokens);
	free(prompt);
	free_tokens(tokens);
	return (0);
}
