/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/18 18:19:35 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	char	*line;
	t_token	*tokens;

	(void) ac;
	(void) av;
	prompt = get_prompt(env);
	line = readline(prompt);
	printf("%s", line);
	tokens = lexer(line);
	if (!tokens)
	{
		printf("Lexer error\n");
		free(line);
		free(prompt);
		return (1);
	}
	while (tokens)
	{
		printf("\nToken: %s\n", tokens->str);
		tokens = tokens->next;
	}
	free(prompt);
	return (0);
}
