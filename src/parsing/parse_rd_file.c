/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rd_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:44 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/14 18:40:09 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_rd_file(t_token *token);
static int	set_rd(t_token *token);

/**
 * @brief Parse a redirection token, allocate its data and set its file.
 * 
 * @param token Redirection token to parse.
 * 
 * @return 0 on success, 1 on failure.
 */
int	parse_rd_file(t_token *token)
{
	if (!token || (token->type != T_REDIR_IN
			&& token->type != T_REDIR_OUT && token->type != T_APPEND))
		return (1);
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return (1);
	if (!token->next || !is_word(token->next))
		return (1);
	token->data->rd = malloc(sizeof(t_rd));
	if (!token->data->rd)
	{
		free(token->data);
		token->data = NULL;
		return (1);
	}
	return (set_rd(token));
}

/**
 * @brief Set the redirection file from the next token.
 * 
 * @param token Redirection token to complete.
 * 
 * @return 0 on success, 1 on failure.
 */
static int	set_rd(t_token *token)
{
	t_token	*tmp;

	token->data->rd->file = malloc(sizeof(t_rd_file));
	if (!token->data->rd->file)
	{
		free(token->data->rd);
		token->data->rd = NULL;
		return (1);
	}
	token->data->rd->file->fd = -1;
	token->data->rd->file->filename = NULL;
	token->data->rd->file->filename = ft_strdup(token->next->str);
	if (!token->data->rd->file->filename)
	{
		free(token->data->rd);
		token->data->rd = NULL;
		return (1);
	}
	tmp = token->next;
	if (tmp)
		token->next = token->next->next;
	free_token(tmp);
	return (0);
}
