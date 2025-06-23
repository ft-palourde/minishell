/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:03 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:36:04 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/** check_option
 * @str: echo argument
 * 
 * check if the argument contains -n to prevent echo to display a newline
 *
 * Returns: 1 if yes, 0 else
 */
static int	check_option(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i] == 'n')
				i++;
			if (!str[i])
				return (1);
		}
		i++;
	}
	return (0);
}

/** bi_echo - Builtin echo
 * @arg: arguments given in input
 * 
 * displays all the arguments on the required fd
 * (STDOUT if no pipe or redirection)
 *
 * Returns: 0
 */
int	bi_echo(char **arg)
{
	int		option;
	int		i;

	i = 0;
	option = check_option(arg[0]);
	if (option)
		i++;
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
		if (arg[i])
			printf(" ");
	}
	if (!option)
		printf("\n");
	return (0);
}

/* //test main
int main(int ac, char **av)
{
	(void) ac;
	bi_echo(&av[1]);
	return (0);
} */