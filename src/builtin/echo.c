/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:03 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/18 13:41:54 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

//envoyer un arg qui contient tout l'argument apres echo sans aucun traitement

/* 
specific cases :
if echo "blabla"		-> blabla\n
if echo "-n" "blabla"	-> blabla%
if echo -n blabla		-> blabla%
if echo "-n blabla"		-> blabla\n
if echo -n "blabla"		-> blabla%
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

void	bi_echo(char **arg)
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
}

/* //test main
int main(int ac, char **av)
{
	(void) ac;
	bi_echo(&av[1]);
	return (0);
} */