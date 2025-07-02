/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:00:49 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/02 17:03:17 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/** token_is_operator - token checker
 * @token: the token to check
 * 
 * checks if token type is T_OR_IF || T_AND_IF || T_PIPE || T_HEREDOC
 *
 * Returns: 1 if yes, no else
 */
static int	token_is_operator(t_token *token)
{
	t_token_type	type;

	type = token->type;
	if (type == T_OR_IF || type == T_AND_IF || type == T_PIPE)
		return (1);
	return (0);
}

/** need_sort
 * @token: the token to check
 * 
 * check if the token given in argument is the first of 
 * a part of the list that needs to be sorted
 *
 * Returns:
 * n elements to skip until sorting is needed
 * 0 else
 */
static int	needs_sort(t_token *token)
{
	t_token	*cursor;
	int		cmd;
	int		redir;
	int		i;

	cmd = 0;
	redir = 0;
	cursor = token;
	i = 0;
	while (cursor && !token_is_operator(cursor))
	{
		if (cursor->type == T_CMD)
			cmd ++;
		if ((is_redir(cursor->type) || cursor->type == T_HEREDOC) && !cmd)
		{
			redir++;
			i++;
		}
		cursor = cursor->next;
	}
	if (redir && cmd)
		return (i);
	return (0);
}

static t_token	*add_after_cmd(t_token *token, int sorted, t_token *head)
{
	t_token	*cursor;
	t_token	*nxt;
	t_token	*tmp;
	int		i;

	cursor = token;
	i = 0;
	nxt = token->next;
	while (cursor && cursor->type != T_CMD)
		cursor = cursor->next;
	if (head)
		head->next = cursor;
	while (cursor && i < sorted)
	{
		cursor = cursor->next;
		i++;
	}
	tmp = cursor->next;
	cursor->next = token;
	token->next = tmp;
	return (nxt);
}

void	sort_tokens(t_ms *ms)
{
	int		to_sort;
	int		i;
	int		lock_first;
	t_token	*head;
	t_token	*cursor;

	cursor = ms->token;
	lock_first = 0;
	head = 0;
	while (cursor)
	{
		to_sort = needs_sort(cursor);
		i = 0;
		while (i < to_sort)
		{
			cursor = add_after_cmd(cursor, i, head);
			if (!lock_first)
				ms->token = cursor;
			i++;
		}
		while (cursor && !token_is_operator(cursor))
			cursor = cursor->next;
		head = cursor;
		if (!cursor)
			break ;
		cursor = cursor->next;
		lock_first = 1;
	}
}

/* void	loop_sort(t_token *cursor, int *lock_first)
{
	int	i;
	int	to_sort;

	while (cursor)
	{
		to_sort = needs_sort(cursor);
		i = 0;
		while (i < to_sort)
		{
			cursor = add_after_cmd(cursor, i, head);
			if (!lock_first)
				ms->token = cursor;
			i++;
		}
		while (cursor && !token_is_operator(cursor))
			cursor = cursor->next;
		head = cursor;
		if (!cursor)
			break ;
		cursor = cursor->next;
		lock_first = 1;
	}
} */
