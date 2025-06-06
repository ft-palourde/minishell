/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:24:47 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/06 18:38:15 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_is_operator(t_token *token)
{
	t_token_type	type;

	type = token->type;
	if (type == T_OR_IF || type == T_AND_IF || type == T_PIPE)
		return (1);
	return (0);
}

int	needs_sort(t_token *token)
{
	t_token	*cursor;
	int		cmd;
	int		redir;

	cmd = 0;
	redir = 0;
	cursor = token;
	while (cursor && !token_is_operator(cursor))
	{
		if (cursor->type == T_CMD)
			cmd ++;
		if (is_redir(cursor->type) && !cmd)
			redir++;
		cursor = cursor->next;
	}
	if (redir && cmd)
		return (1);
	return (0);
}

t_token	*get_next_cmd(t_token *token)
{
	t_token	*cursor;

	cursor = token;
	while (cursor && cursor->type != T_CMD)
		cursor = cursor->next;
	return (cursor);
}

void	replace_redir(t_token *token)
{
	t_token	*found;
	t_token	*cmd;
	t_token	*cursor;

	cursor = token;
	found = cursor->next;
	cursor->next = found->next;
	cmd = get_next_cmd(found);
	found->next = cmd->next;
	cmd->next = found;
}

void	print_token_list(t_token *token)
{
	while (token)
	{
		printf("[%d]%s\n", token->type, token->str);
		token = token->next;
	}
}

void	sort_token(t_ms *ms)
{
	t_token	*cursor;

	cursor = ms->token;
	while (cursor && cursor->next)
	{
		if (cursor && needs_sort(cursor))
		{
			while (cursor->next && cursor->next->type != T_CMD)
				if (is_redir(cursor->next->type))
					replace_redir(cursor);
			if (cursor->next && token_is_operator(cursor))
				break ;
			cursor = cursor->next;
		}
		else
			while (cursor->next && !token_is_operator(cursor))
				cursor = cursor->next;
		cursor = cursor->next;
	}
	print_token_list(ms->token);
}

int	exec_init(t_ms *ms)
{
	sort_token(ms);
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
