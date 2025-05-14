/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/14 17:50:09 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_all(t_ms *ms)
{
	(void) ms;
}

void	wait_pid(t_ms *ms)
{
	(void) ms;
}

int	ms_exec(t_ms *ms)
{
	int	pid;

	exec_init(ms);
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 1);
	if (!pid)
	{
		ms->tree = build_tree(ms->token);
		exec_tree(ms->tree, ms);
		wait_pid(ms);
	}
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
	printf("%s", line);
	tokens = parse(line);
	if (!tokens)
	{
		printf("\nParsing error\n");
		free(line);
		free(prompt);
		return (1);
	}
	// debug_display_token_args(tokens);
	free(prompt);
	free_tokens(tokens);
	return (0);
}
