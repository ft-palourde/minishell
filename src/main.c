/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/01 17:10:24 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("\nLexer error\n");
		free(line);
		free(prompt);
		return (1);
	}
	debug_display_token_args(tokens);
	free(prompt);
	free_tokens(tokens);
	return (0);
}
