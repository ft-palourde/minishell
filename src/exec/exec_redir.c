/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:55 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/09 18:49:37 by tcoeffet         ###   ########.fr       */
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
		ms->file_in = open(path, O_RDONLY);
	else if (token->type == T_APPEND)
		ms->file_out = open(path, O_WRONLY, O_APPEND);
	else
		ms->file_out = open(path, O_WRONLY, O_TRUNC);
	if (ms->file_in == -1 || ms->file_out == -1)
		perror("open failed");
}

void	get_redirs(t_tree *node, t_ms *ms)
{
	if (is_redir(node->left->token->type))
		exec_redir(node->left->token, ms);
	if (is_redir(node->right->token->type))
		exec_redir(node->right->token, ms);
	node->token->in_fd = ms->file_in;
	node->token->out_fd = ms->file_out;
}
