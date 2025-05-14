/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/26 17:40:36 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	clear_all(t_ms *ms)
{
	(void) ms;
}

int	wait_all(t_ms *ms)
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
	build_tree(ms);
	if (!ms->tree)
		return (0);
	exec_tree(ms->tree, ms);
	ms->retval = wait_all(ms);
	return (0);
}

t_ms	*init_ms_struct(char **env)
{
	t_ms	*new;

	new = ft_calloc(1, sizeof(t_ms));
	new->env = env;
	new->pid = ft_calloc(1, 1);
	if (!new->pid)
		return (free(new), NULL);
	new->pfd = ft_calloc(1, 1);
	if (!new->pfd)
		return (free(new->pid), free(new), NULL);
	return (new);
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_ms	*ms;

	(void)ac;
	(void)av;
	prompt = get_prompt(env);
	if (!prompt)
		return (1);
	while (1)
	{
		ms = init_ms_struct(env);
		if (!ms)
			break ;
		ms->token = parse(readline(prompt));
		if (!ms->token)
			break ;
		ms_exec(ms);
		if (ms->exit)
			break ;
		write(1, "\n", 1);
		minishell_cleaner(ms);
	}
	free(prompt);
	free(ms);
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
