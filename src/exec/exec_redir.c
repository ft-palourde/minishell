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

	path = token->data->rd->file->filename;
	if (!path)
		return ;
	if (token->type == T_REDIR_IN)
		ms->file_in = open(path, O_RDONLY | O_CREAT, 0644);
	else if (token->type == T_APPEND)
		ms->file_out = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (token->type == T_REDIR_OUT)
		ms->file_out = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	// else
	// 	printf("tree builder error, [%s] not a redirect", token->str);
	if (ms->file_in == -1 || ms->file_out == -1)
	{
		perror("open failed");
		return ;
	}
	if (ms->file_in)
		add_fd(ms->file_in, ms);
	if (ms->file_out)
		add_fd(ms->file_out, ms);
}
