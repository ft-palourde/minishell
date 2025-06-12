/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:31:41 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/09 19:08:03 by tcoeffet         ###   ########.fr       */
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

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	var_exists(char **env, char *var)
{
	char	*name;
	int		i;
	int		len;

	i = 0;
	name = get_var_name(var);
	if (!name)
		return (-1);
	len = ft_strlen(name);
	while (env[i])
	{
		if (strncmp(env[i], name, len))
			i++;
		else
			return (free(name), 1);
	}
	free(name);
	return (0);
}

int	var_is_empty(char *var)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 1;
	while (var[i] != '=')
		i++;
	i++;
	if (!var[i])
		return (1);
	if (var[i] == '\'' || var[i] == '\"')
	{
		quote = var[i];
		while (var[i + j] && var[i + j] != quote)
			j++;
		if (!var[i + j])
			return (0);
		if (j == 1)
			return (1);
	}
	return (0);
}

int is_var(char *var)
{
	int	has_name;
	int	has_sign;
	int	i;

	i = 1;
	has_sign = 0;
	has_name = 0;
	if (!var[0])
		return (0);
	while (var[i] && is_space(var[i]))
		i++;
	while (var[i])
	{
		if (var[i] == '=')
			has_sign = 1;
		else
			has_name = 1;
		i++;
	}
	if (has_name && has_sign)
		return (1);
	return (0);
}
