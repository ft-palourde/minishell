/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:14 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/01 18:19:26 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*parse(char *input);
static int	check_syntax_error(t_token *tokens);
static bool	is_builtin_cmd(const char *cmd);
void		merge_word_tokens(t_token *token);
void		set_cmd_args(t_token *token);
void		handle_cmd(t_token *token);
/* ************************************************************************** */

t_token	*parse(char *input)
{
	t_token	*cursor;
	t_token	*tokens;

	tokens = lexer(input);
	cursor = tokens;
	while (cursor)
	{
		if (check_syntax_error(cursor))
		{
			free_tokens(tokens);
			return (NULL);
		}
		//TODO : here handle operators -> store word token in token's filename attribute BEFORE handle_cmd
		if (cursor->type == T_WORD)
		{
			handle_cmd(cursor);//rename in parse_cmd ?
			if (!cursor->data || !cursor->data->cmd)
			{
				free_tokens(tokens);
				return (NULL);
			}
		}
		// if (cursor)
			// printf("cursor type: %d\n", cursor->type);
		if (!cursor)
			break ;
		cursor = cursor->next;
	}
	// printf("parse: end\n");
	return (tokens);
}

/* 
returns 1 if there is a syntax error, 0 otherwise
*/
int	check_syntax_error(t_token *tokens)
{
	t_token	*cursor;

	cursor = tokens;
	while (cursor)
	{
		if (cursor->type == T_PIPE && (!cursor->next
				|| cursor->next->type == T_PIPE))
		{
			ft_putstr_fd("unexpected token `|'\n", 2);
			return (1);
		}
		if (cursor->type == T_REDIR_IN || cursor->type == T_REDIR_OUT
			|| cursor->type == T_APPEND || cursor->type == T_HEREDOC)
		{
			if (!cursor->next || cursor->next->type != T_WORD)
			{
				ft_putstr_fd("syntax error: missing file after rd\n", 2);
				return (1);
			}
		}
		cursor = cursor->next;
	}
	return (0);
}

/* 
allocate a new t_cmd struct and fill it with the command and its arguments
the command is the first word in the token list
the arguments are the words that follow the command
the command is stored in token->data->cmd->args[0]
if the command is a builtin, is_builtin is set to true
*/
void	handle_cmd(t_token *token)
{
	if (!token || token->type != T_WORD)
		return ;
	// printf("\nhandle_cmd\n");
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return ;
	token->data->cmd = new_cmd();
	if (!token->data->cmd)
		return ;
	token->data->cmd->is_builtin = is_builtin_cmd(token->str);
	set_cmd_args(token);
	if (!token->data->cmd)
	{
		free(token->data);
		return ;
	}
	token->type = T_CMD;
	// printf("handle_cmd end\n");
}

/* 
returns true if the command is a builtin, false otherwise
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
int	get_arg_count(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type == T_WORD)
	{
		count++;
		token = token->next;
	}
	// printf("get_arg_count: %d\n", count);
	return (count);
}

void	set_cmd_args(t_token *token)
{
	int		arg_count;

	// printf("set_cmd_args\n");
	if (!token || token->type != T_WORD || !token->data)
		return ;
	arg_count = get_arg_count(token);

	if (arg_count == 0)
	{
		free(token->data);
		return ;
	}
	// printf("coucou\n");

	token->data->cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!token->data->cmd->args)
		return ;
	merge_word_tokens(token);
	// printf("set_cmd_args end\n");
}

void	merge_word_tokens(t_token *token)
{
	t_token	*cursor;
	t_token	*to_free;
	int		i;

	// printf("merge_word_tokens\n");
	if (!token || token->type != T_WORD)
		return ;
	cursor = token;
	i = 0;
	while (cursor && cursor->type == T_WORD)
	{
		token->data->cmd->args[i] = ft_strdup(cursor->str);
		to_free = cursor;
		cursor = cursor->next;
		if (i > 0)
			free_token(to_free);
		i++;
	}
	token->data->cmd->args[i] = NULL;
	token->next = cursor;
	// printf("merge_word_tokens end\n");
}
