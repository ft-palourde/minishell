#include "minishell.h"

static int	token_is_operator(t_token *token)
{
	t_token_type	type;

	type = token->type;
	if (type == T_OR_IF || type == T_AND_IF || type == T_PIPE)
		return (1);
	return (0);
}

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
		if (is_redir(cursor->type) && !cmd)
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

static t_token	*add_after_cmd(t_token *token, int sorted)
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
/* 
//DEBUG
void	print_token_list(t_token *token)
{
	while (token)
	{
		printf("[%d]%s", token->type, token->str);
		if (is_redir(token->type))
			printf(" %s", token->data->rd->file->filename);
		printf("\n");
		token = token->next;
	}
} */

void	sort_tokens(t_ms *ms)
{
	int		to_sort;
	int		i;
	int		lock_first;
	t_token	*cursor;

	cursor = ms->token;
	lock_first = 0;
	while (cursor)
	{
		to_sort = needs_sort(cursor);
		i = 0;
		while (i < to_sort)
		{
			cursor = add_after_cmd(cursor, i);
			if (!lock_first)
				ms->token = cursor;
			i++;
		}
		while (cursor && !token_is_operator(cursor))
			cursor = cursor->next;
		if (!cursor)
			return ;
		cursor = cursor->next;
		lock_first = 1;
	}
}
