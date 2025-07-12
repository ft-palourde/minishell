/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:24:47 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/25 14:41:20 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** exec_heredoc - execute a heredoc node
 * @node: current tree node carrying a T_HEREDOC type token
 * @ms: minishell struct
 * 
 * checks if the heredoc needs to be piped in something and dups
 * STDIN or STDOUT if needed before writing its content in the 
 * wanted fd.
 *
 * Returns: 1 on malloc failed, 0 else
 */
int	exec_init(t_ms *ms)
{
	sort_tokens(ms);
	if (!ms->token)
		return (1);
	if (get_heredocs_pfd(ms))
		return (1);
	return (0);
}

/** exec_heredoc - execute a heredoc node
 * @node: current tree node carrying a T_HEREDOC type token
 * @ms: minishell struct
 * 
 * checks if the heredoc needs to be piped in something and dups
 * STDIN or STDOUT if needed before writing its content in the 
 * wanted fd.
 *
 * Returns: 1 on malloc failed, 0 else
 */
int	exec_tree(t_tree *root, t_ms *ms)
{
	if (!root)
		return (1);
	if (root->token->type == T_PIPE)
		exec_pipe(root, ms);
	if (is_redir(root->token->type))
		exec_redir(root, ms);
	if (root->token->type == T_HEREDOC)
		ms->file_in = root->token->data->rd->heredoc->fd[0];
	exec_tree(root->left, ms);
	exec_tree(root->right, ms);
	if (ms->open_failed)
	{
		ms->retval = 1;
		return (0);
	}
	if (root->token->type == T_CMD && !ms->open_failed)
		exec_cmd(root, ms);
	return (0);
}
