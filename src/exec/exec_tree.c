/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:24:47 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/10 16:20:32 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_init(t_ms *ms)
{
	sort_tokens(ms);
	if (!ms->token)
		return (1);
	if (get_heredocs_pfd(ms))
		return (1);
	return (0);
}

int	exec_tree(t_tree *root, t_ms *ms)
{
	if (!root)
		return (1);
	if (root->token->type == T_PIPE)
		exec_pipe(root, ms);
	if (is_redir(root->token->type))
		exec_redir(root->token, ms);
	exec_tree(root->left, ms);
	exec_tree(root->right, ms);
	if (root->token->type == T_CMD)
		exec_cmd(root, ms);
	if (root->token->type == T_HEREDOC)
		exec_heredoc(root, ms);
	return (0);
}
