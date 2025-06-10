/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 14:30:54 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variable(t_token *token, char **env)
{
	char	**args;
	int		i;

	args = token->data->cmd->args;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\0')
		{
			i++;
			continue ;
		}
		args[i] = str_expand(args[i], env);
		if (ft_strchr(args[i], '*'))
			expand_globbing(args[i]);
		i++;
	}
}



/* while (env[i])
	{
		name = get_var_name(env[i]);
		if (!name)
			return (1);
		value = get_var_value(env[i]);
		if (!value)
			return (free(name), 1);
		printf("export %s=\"%s\"\n", name, value);
		free(name);
		free(value);
		i++;
	} */

