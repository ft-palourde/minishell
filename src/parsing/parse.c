/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:14:14 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/29 18:03:20 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*parse(char *input);
static int	check_syntax_error(t_token *tokens);
static bool	is_builtin_cmd(const char *cmd);
void		get_cmd_args(t_token *token, t_cmd *cmd);
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
		if (cursor->type == T_WORD)
		{
			handle_cmd(cursor);
			while (cursor->next && cursor->next->type == T_WORD)
				cursor = cursor->next;
		}
		cursor = cursor->next;
	}
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


// si le token est un mot, on met le mot dans le token et dans data->cmd->args[0]
// on va vérifier si le mot est un builtin ou pas
// on va ensuite regarder le token suivant.
// tant que le token suivant est un mot, on va l'ajouter à data->cmd->args[i], i++
// on va continuer jusqu'à ce qu'on trouve un token qui n'est pas un mot

/* 
allocate a new t_cmd struct and fill it with the command and its arguments
the command is the first word in the token list
the arguments are the words that follow the command
the command is stored in token->data->cmd->args[0]
if the command is a builtin, is_builtin is set to true
*/
void	handle_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	get_cmd_args(token, cmd);
	token->data->cmd = cmd;
	//cmd->path = find_path(cmd->args[0]);
	cmd->is_builtin = is_builtin_cmd(cmd->args[0]);
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
	return (count);
}
// void	get_cmd_arg

//find_paths(char *cmd)

void	get_cmd_args(t_token *token, t_cmd *cmd)
{
	int		i;
	int		arg_count;

	arg_count = get_arg_count(token);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return ;
	i = 0;
	while (token && token->type == T_WORD)
	{
		cmd->args[i] = ft_strdup(token->str);
		token = token->next;
		i++;
	}
	cmd->args[i] = NULL;
	token->data->cmd = cmd;
}
