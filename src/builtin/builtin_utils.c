/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:31:41 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/15 11:53:04 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_token *token)
{
	const char	*cmd = token->data->cmd->args[0];

	token->data->cmd->is_builtin = B_NONE;
	if (!ft_strncmp(cmd, "exit", 5))
		token->data->cmd->is_builtin = B_EXIT;
	if (!ft_strncmp(cmd, "echo", 5))
		token->data->cmd->is_builtin = B_ECHO;
	if (!ft_strncmp(cmd, "pwd", 4))
		token->data->cmd->is_builtin = B_PWD;
	if (!ft_strncmp(cmd, "export", 7))
		token->data->cmd->is_builtin = B_EXPORT;
	if (!ft_strncmp(cmd, "cd", 3))
		token->data->cmd->is_builtin = B_CD;
	if (!ft_strncmp(cmd, "env", 4))
		token->data->cmd->is_builtin = B_ENV;
	if (!ft_strncmp(cmd, "unset", 6))
		token->data->cmd->is_builtin = B_UNSET;
	return (token->data->cmd->is_builtin);
}

char	*get_var_name(char *var)
{
	int		i;
	char	*name;

	i = 0;
	while (var[i] != '=')
		i++;
	name = ft_strndup(var, i);
	if (!name)
		return (perror("malloc"), NULL);
	return (name);
}

char	*get_var_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] != '=')
		i++;
	value = ft_strdup(var + i + 1);
	if (!value)
		return (perror("malloc"), NULL);
	return (value);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
