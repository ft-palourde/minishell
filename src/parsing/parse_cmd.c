/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:25:12 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 22:55:47 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_cmd(t_token *token);
static bool	is_builtin_cmd(const char *cmd);
int			get_arg_count(t_token *token);
static int	set_cmd_args(t_token *token);
int			merge_word_tokens(t_token *token, int i);

/**
 * @brief Parse a command token, allocate its data and set its arguments.
 * 
 * @param token Token to parse and convert to CMD type.
 * 
 * @return 0 on success, 1 on failure.
 */
int	parse_cmd(t_token *token)
{
	if (!token || token->type != T_WORD)
		return (1);
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return (1);
	token->data->cmd = new_cmd();
	if (!token->data->cmd)
		return (1);
	token->data->cmd->is_builtin = is_builtin_cmd(token->str);
	if (set_cmd_args(token))
		return (1);
	if (!token)
		return (1);
	if (!token->data->cmd)
	{
		free(token->data);
		return (1);
	}
	token->type = T_CMD;
	return (0);
}

/**
 * @brief Check if a command is a shell builtin.
 * 
 * @param cmd Command string to check.
 * 
 * @return true if it's a builtin, false otherwise.
 */
static bool	is_builtin_cmd(const char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

/**
 * @brief Count the number of consecutive WORD tokens (arguments).
 * 
 * @param token Current token.
 * 
 * @return Number of argument tokens.
 */
int	get_arg_count(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == T_WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

/**
 * @brief Set command arguments by allocating and copying tokens.
 * 
 * @param token Token to populate with command arguments.
 * 
 * @return 0 on success, 1 on failure.
 */
static int	set_cmd_args(t_token *token)
{
	int		i;
	int		arg_count;

	i = 0;
	if (!token || token->type != T_WORD || !token->data)
		return (1);
	arg_count = get_arg_count(token);
	if (arg_count == 0)
		return (1);
	token->data->cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!token->data->cmd->args)
		return (1);
	if (merge_word_tokens(token, i))
		return (1);
	return (0);
}

/**
 * @brief Merge consecutive WORD tokens into command arguments.
 * 
 * @param token Command token to populate.
 * @param i Index counter for arguments (usually starts at 0).
 * 
 * @return 0 on success, 1 on failure.
 */
int	merge_word_tokens(t_token *token, int i)
{
	t_token	*cursor;
	t_token	*to_free;
	char	*dup;

	if (!token || token->type != T_WORD)
		return (1);
	cursor = token;
	i = 0;
	while (cursor && cursor->type == T_WORD)
	{
		if (!token->data->cmd->args)
			return (1);
		dup = ft_strdup(cursor->str);
		if (!dup)
			return (1);
		token->data->cmd->args[i] = dup;
		to_free = cursor;
		cursor = cursor->next;
		if (i > 0)
			free_token(to_free);
		i++;
	}
	token->data->cmd->args[i] = NULL;
	token->next = cursor;
	return (0);
}
