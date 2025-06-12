/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:55 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/09 17:53:07 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

int	open_failed(char *path, t_ms *ms)
{
	if (ms->file_in == -1 || ms->file_out == -1)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": can't access file.\n", STDERR_FILENO);
		ms->open_failed = 1;
		return (1);
	}
	return (0);
}

void	exec_redir(t_token *token, t_ms *ms)
{
	char	*path;
	int		out;
	int		in;

	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	if (ms->open_failed)
		return ;
	path = token->data->rd->file->filename;
	if (!path)
		return ;
	if (token->type == T_REDIR_IN)
		in = open(path, O_RDONLY | O_CREAT, 0644);
	else if (token->type == T_APPEND)
		out = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (token->type == T_REDIR_OUT)
		out = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_failed(path, ms))
		return ;
	if (in != STDIN_FILENO)
		add_fd(ms->file_in, ms);
	if (out != STDOUT_FILENO)
		add_fd(out, ms);
	ms->file_in = in;
	ms->file_out = out;
}
