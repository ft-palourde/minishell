/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:08 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 18:39:29 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** exit_arg_is_num - checks if the whole string is made of digits
 * @str: the string to check
 * 
 * checks if every elements of the string is a digit
 * displays an error message if the string is not digits
 * 
 * returns : 0 if not or if the string is empyt, 1 else.
 */
static int	exit_arg_is_num(char *str)
{
	int	i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putendl_fd("minishell : exit : numeric argument required", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

/** bi_exit - exit the shell
 * @ms: minishell struct
 * 
 * sets ms->exit to 1 to stop calling cmds in main()
 * 
 * returns : 0
 */
int	bi_exit(t_ms *ms, char **arg)
{
	ms->exit = ms->retval;
	if (arg && arg[1])
	{
		if (exit_arg_is_num(arg[1]))
			ms->exit = ft_atoi(arg[1]);
		else
			ms->exit = 2;
	}
	else if (g_sig == SIGINT)
		ms->exit = 130;
	return (0);
}
