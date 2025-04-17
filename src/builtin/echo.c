/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:03 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/17 19:50:09 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*echo;
	char	*tmp;

	i = 0;
	option = check_option(arg[0]);
	if (option)
		i++;
	tmp = ft_strdup("");
	if (!tmp)
		return ;
	while (arg[i])
	{
		tmp = ft_strjoin(echo, arg[i]);
		if (!tmp)
			return ;
		free(echo);
		echo = tmp;
	}
	ft_putstr(echo);
	free(echo);
}
