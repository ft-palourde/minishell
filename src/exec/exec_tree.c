/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:24:47 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/14 17:09:39 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_expand(char *str, char **env)
{
	char	*new;

	(void) env;
	new = ft_strdup(str);
	return (new);
}

int	is_redir(t_token_type type)
{
	if (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_APPEND)
		return (1);
	return (0);
}

int	exec_init(t_ms *ms)
{
	(void) ms;
	//recupere le contenu de tous les heredoc dans des pipes et
	//range leur pfd dans une list chainee
	
	//initialise le tableau de pid
	return (0);
}

int	exec_tree(t_tree *root, t_ms *ms)
{
	if (!root)
		return (1);
	if (root->token->type == T_PIPE)
		exec_pipe(root, ms);
	exec_tree(root->left, ms);
	exec_tree(root->right, ms);
	if (root->token->type == T_CMD)
		exec_cmd(root, ms);
	if (root->token->type == T_HEREDOC)
		exec_heredoc(root->token, ms);
	return (0);
}
