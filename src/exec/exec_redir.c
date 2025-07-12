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

/** set_ms_fd - set variables in ms struct after redir
 * @in: in variable from exec_redir function
 * @out: out variable from exec_redir function
 * @ms: minishell struct
 * 
 * sets the fd in ms->file_in or ms->file_out depending on where the
 * redirection is pointing.
 *
 * Returns: void
 */
void	set_ms_fd(int in, int out, t_ms *ms)
{
	if (in != STDIN_FILENO)
		ms->file_in = in;
	if (out != STDOUT_FILENO)
		ms->file_out = out;
}

int	rd_has_cmd(t_tree *node)
{
	while (node->parent && node->parent->token->type != T_PIPE)
	{
		if (node->parent->token->type == T_CMD)
			return (1);
		node = node->parent;
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
int	exec_redir(t_tree *node, t_ms *ms)
{
	char	*path;
	int		out;
	int		in;

	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	if (ms->open_failed)
		return (1);
	if (!rd_has_cmd(node))
		return (0);
	path = str_expand(node->token->data->rd->file->filename, ms);
	if (!path)
		return (1);
	if (node->token->type == T_REDIR_IN)
		in = open(path, O_RDONLY, 0644);
	else if (node->token->type == T_APPEND)
		out = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (node->token->type == T_REDIR_OUT)
		out = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	set_ms_fd(in, out, ms);
	if (open_failed(path, ms) || \
		((in != STDIN_FILENO && add_fd(ms->file_in, ms)) || \
			(out != STDOUT_FILENO && add_fd(out, ms))))
		return (free(path), 1);
	return (free(path), 0);
}
