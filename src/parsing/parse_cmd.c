/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:25:12 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 16:45:22 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_cmd(t_token *token);
static bool	is_builtin_cmd(const char *cmd);
int			get_arg_count(t_token *token);
static void	set_cmd_args(t_token *token);
void		merge_word_tokens(t_token *token);

/* 
allocate a new t_cmd struct and fill it with the command and its arguments
the command is the first word in the token list
the arguments are the words that follow the command
the command is stored in token->data->cmd->args[0]
if the command is a builtin, is_builtin is set to true
*/

/** @brief parse_cmd - alloc the union and initiate cmd in current token.
 * 
 * @param token the current token to set as CMD.
 * 
 * Set its boolean is_builtin.
 * Fills the cmd args.
 * Changes WORD type to CMD.
 */
void	parse_cmd(t_token *token)
{
	if (!token || token->type != T_WORD)
		return ;
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return ;
	token->data->cmd = new_cmd();
	if (!token->data->cmd)
		return ;
	token->data->cmd->is_builtin = is_builtin_cmd(token->str);
	set_cmd_args(token);
	if (!token)
		return ;
	if (!token->data->cmd)
	{
		free(token->data);
		return ;
	}
	token->type = T_CMD;
}

/** @brief is_builtin_cmd - check if the given command is a builtin.
 * 
 * @param cmd the command to compare with builtins.
 *  
 * @returns returns 1 if true, 0 otherwise.
 */
static bool	is_builtin_cmd(const char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

/* 
returns the number of arguments in the command, including the command itself
*/
/** @brief get_arg_count - Counts the number of WORD token after a CMD.
 * 
 * @param token the current CMD.
 *  
 * @returns the number of args to merge (int).
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

/** @brief set_cmd_args - Alloc and fill cmd args.
 * 
 * @param token the t_token of type CMD to complete.
 * 
 * Get the count of args to set, alloc the cmd args array.
 * Then merge the next args tokens in the current cmd token.
 */
static void	set_cmd_args(t_token *token)
{
	int		arg_count;

	if (!token || token->type != T_WORD || !token->data)
		return ;
	arg_count = get_arg_count(token);
	if (arg_count == 0)
	{
		free(token->data);
		return ;
	}
	token->data->cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!token->data->cmd->args)
		return ;
	merge_word_tokens(token);
}

/** @brief merge_word_tokens - merge the next word tokens as cmd args.
 * 
 * @param token the cmd token.
 * Set each next word token->str as current cmd token args, 
 * and free each next word token set as args.
 */
void	merge_word_tokens(t_token *token)
{
	t_token	*cursor;
	t_token	*to_free;
	int		i;
	char	*dup;

	if (!token || token->type != T_WORD)
		return ;
	cursor = token;
	i = 0;
	while (cursor && cursor->type == T_WORD)
	{
		if (!token->data->cmd->args)
			return (free_token(token));
		dup = ft_strdup(cursor->str);
		if (!dup)
			return (free_token(token));
		token->data->cmd->args[i] = dup;
		to_free = cursor;
		cursor = cursor->next;
		if (i > 0)
			free_token(to_free);
		i++;
	}
	token->data->cmd->args[i] = NULL;
	token->next = cursor;
}
