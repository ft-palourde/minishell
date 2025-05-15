/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/26 17:41:55 by tcoeffet         ###   ########.fr       */
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
	if (!new)
		return (NULL);
	new->env = set_env(env, 1);
	return (new);
}

int	reset_ms_struct(t_ms *ms)
{
	ms->exit = 0;
	ms->file_in = 0;
	ms->file_out = 0;
	ms->retval = 0;
	ms->token = 0;
	ms->tree = 0;
	ms->pid = ft_calloc(1, sizeof(int));
	if (!ms->pid)
		return (perror("malloc"), 1);
	ms->pfd = ft_calloc(1, sizeof(int));
	if (!ms->pfd)
		return (perror("malloc"), free(ms->pid), 1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_ms	*ms;

	(void)ac;
	(void)av;
	prompt = get_prompt(env);
	ms = init_ms_struct(env);
	if (!ms)
		return (perror("malloc"), 1);
	if (!prompt)
		return (1);
	while (1)
	{
		if (reset_ms_struct(ms))
			break ;
		ms->token = parse(readline(prompt));
		if (ms->token)
		{
			ms_exec(ms);
			if (ms->exit)
				break ;
			minishell_cleaner(ms);
		}
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
