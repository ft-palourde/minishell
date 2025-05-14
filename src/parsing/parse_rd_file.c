/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rd_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:44 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/14 10:22:21 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_rd_file(t_token *token);
static void	set_rd(t_token *token);

// token->data->rd->file = malloc(sizeof(t_rd_file));
void	parse_rd_file(t_token *token)
{
	// printf("\nparse_rd_file\n");
	if (!token || (token->type != T_REDIR_IN
			&& token->type != T_REDIR_OUT && token->type != T_APPEND))
		return ;
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return ;
	if (!token->next || !is_word(token->next))
		return ;
	token->data->rd = malloc(sizeof(t_rd));
	if (!token->data->rd)
	{
		free(token->data);
		token->data = NULL;
		return ;
	}
	set_rd(token);
}

static void	set_rd(t_token *token)
{
	t_token	*tmp;

	token->data->rd->file = malloc(sizeof(t_rd_file));
	if (!token->data->rd->file)
	{
		free(token->data->rd);
		token->data->rd = NULL;
		return ;
	}
	token->data->rd->file->fd = -1;
	token->data->rd->file->filename = NULL;
	token->data->rd->file->filename = ft_strdup(token->next->str);
	if (!token->data->rd->file->filename)
	{
		free(token->data->rd);
		token->data->rd = NULL;
		return ;
	}
	tmp = token->next;
	token->next = token->next->next;
	free_token(tmp);
}
