/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:55 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/25 13:47:58 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/** open_failed - error checker
 * @path: the file path
 * @ms: minishell struct
 * 
 * display an error message and then set ms->open_failed to 1 to stop executing
 * if the open failed
 *
 * Returns: 1 on open fail, 0 on success
 */
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

/** exec_redir - execute a redir node
 * @node: current tree node carrying a redir type token
 * @ms: minishell struct
 * 
 * expand the content of the path and then open the file pointed to by
 * token->rd->file->filename and stock the new fd at the end of ms->fd
 * and set it in ms->file_in/out
 *
 * Returns: 1 on malloc failed, 0 else
 */
int	exec_redir(t_token *token, t_ms *ms)
{
	char	*path;
	int		out;
	int		in;

	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	if (ms->open_failed)
		return (1);
	path = str_expand(token->data->rd->file->filename, ms);
	if (!path)
		return (1);
	if (token->type == T_REDIR_IN)
		in = open(path, O_RDONLY | O_CREAT, 0644);
	else if (token->type == T_APPEND)
		out = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (token->type == T_REDIR_OUT)
		out = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (open_failed(path, ms))
		return (1);
	if (in != STDIN_FILENO && add_fd(ms->file_in, ms))
		return (perror("malloc"), 1);
	if (out != STDOUT_FILENO && add_fd(out, ms))
		return (perror("malloc"), 1);
	ms->file_in = in;
	ms->file_out = out;
	return (0);
}
