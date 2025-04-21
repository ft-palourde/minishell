/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:30:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/21 18:11:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	char	*line;
	t_token	*tokens;
	t_token	*cursor;

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
	cursor = tokens;
	while (cursor)
	{
		printf("\nToken: %s\n", cursor->str);
		cursor = cursor->next;
	}
	free(prompt);
	free_tokens(tokens);
	return (0);
}

