/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:55 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/01 19:42:36 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	exec_redir(t_token *token, t_ms *ms)
{
	char	*path;

	path = expand_path(token->data->rd->file);
	if (token->type == T_REDIR_IN)
		ms->file_in = open(path, O_RDONLY);
	else
	{
		if (token->data->rd->is_append)
			ms->file_out = open(path, O_WRONLY, O_APPEND);
		else
			ms->file_out = open(path, O_WRONLY, O_TRUNC);
	}
	if (ms->file_in == -1 || ms->file_out == -1)
		perror("open failed");
}
