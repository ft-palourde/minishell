/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rd_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:44 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/02 13:50:09 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_rd_file(t_token *token);
static void	rd_case_in(t_token *token);
static void	rd_case_trunc(t_token *token);
static void	rd_case_append(t_token *token);
static void	switch_rd_case(t_token *token);

// token->data->rd->file = malloc(sizeof(t_rd_file));
void	parse_rd_file(t_token *token)
{
	printf("\nparse_rd_file\n");
	if (!token || (token->type != T_REDIR_IN
			&& token->type != T_REDIR_OUT && token->type != T_APPEND))
		return ;
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return ;
	if (!token->next || !is_word(token->next))
		return ;//TODO : ici mettre le message d'erreur explicite
	token->data->rd = malloc(sizeof(t_rd));
	if (!token->data->rd)
	{
		free(token->data);
		token->data = NULL;
		return ;
	}
	switch_rd_case(token);
}

static void	rd_case_in(t_token *token)
{
	t_token *tmp;

	printf("\nrd_case_in\n");
	if (!token)
		return ;
	if (!token->data || token->type != T_REDIR_IN)
		return ;
	token->data->rd = malloc(sizeof(t_rd));
	if (!token->data->rd)
	{
		free(token->data);
		token->data = NULL;
		return ;
	}
	token->data->rd->file = malloc(sizeof(t_rd_file));
	if (!token->data->rd->file)
	{
		free(token->data->rd);
		token->data->rd = NULL;
		return ;
	}
	token->data->rd->file->fd = -1;
	token->data->rd->file->filename = NULL;
	if (token->next && token->next->type == T_WORD)
	{
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
	else
	{
		free(token->data);
		token->data = NULL;
		return ;
	}
}

static void	rd_case_trunc(t_token *token)
{
	printf("\nrd_case_trunc\n");
	if (!token)
		return ;
	return ;
}

static void	rd_case_append(t_token *token)
{
	printf("\nrd_case_append\n");
	if (!token || !token->data || token->type != T_APPEND)
		return ;
	return ;
}

static void	switch_rd_case(t_token *token)
{
	printf("\nswitch_rd_case\n");
	if (token->type == T_REDIR_IN)
		rd_case_in(token);
	else if (token->type == T_REDIR_OUT)
		rd_case_trunc(token);
	else if (token->type == T_APPEND)
		rd_case_append(token);
	else
	{
		free(token->data);
		token->data = NULL;
	}
}

