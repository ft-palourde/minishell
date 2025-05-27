/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:55 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/27 13:09:40 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	exec_redir(t_token *token, t_ms *ms)
{
	char	*path;

	path = str_expand(token->data->rd->file->filename, ms->env);
	if (!path)
		return ;
	if (token->type == T_REDIR_IN)
		ms->file_in = open(path, O_RDONLY | O_CREAT, 0644);
	else if (token->type == T_APPEND)
		ms->file_out = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		ms->file_out = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (ms->file_in == -1 || ms->file_out == -1)
		perror("open failed");
	if (ms->file_in)
		add_fd(ms->file_in, ms);
	if (ms->file_out)
		add_fd(ms->file_out, ms);
}

void	get_redirs(t_tree *node, t_ms *ms)
{
	int	is_out;
	int	is_in;

	is_out = 0;
	is_in = 0;
	if (node->left && is_redir(node->left->token->type))
	{
		is_in++;
		exec_redir(node->left->token, ms);
	}
	if (node->right && is_redir(node->right->token->type))
	{
		is_out++;
		exec_redir(node->right->token, ms);
	}
	if (is_in)
		node->token->in_fd = ms->file_in;
	if (is_out)
		node->token->out_fd = ms->file_out;
}

void	exec_heredoc(t_token *token, t_ms *ms)
{
	(void) token;
	(void) ms;
}
