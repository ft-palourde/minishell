/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:08 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/13 13:46:45 by tcoeffet         ###   ########.fr       */
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
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/** bi_exit - exit the shell
 * @ms: minishell struct
 * 
 * set the variable ms->exit to order the program to quit,
 * and sets the right return value in ms->exit depending on the
 * arguments given. 
 * 
 * returns : 1 on argument error or 0 if exit is done
 */
int	bi_exit(t_ms *ms, char **arg)
{
	int	arg_count;

	ms->exit = ms->retval;
	if (arg && arg[1] && exit_arg_is_num(arg[1]))
	{
		arg_count = split_len(arg);
		if (arg_count > 2)
		{
			ft_putendl_fd("minishell : exit : too many arguments", 2);
			ms->exit = -1;
			ms->retval = 1;
			return (1);
		}
		ms->exit = ft_atoi(arg[1]);
	}
	else if (arg && arg[1])
	{
		ms->exit = 2;
		ft_putendl_fd("minishell : exit : numeric argument required", 2);
	}
	if (g_sig == SIGINT)
		ms->exit = 130;
	return (0);
}
