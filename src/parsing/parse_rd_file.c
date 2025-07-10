/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rd_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:44 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 18:05:19 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_rd_file(t_token *token);
static int	set_rd(t_token *token);

/** @brief parse_rd_file - Alloc and fill rd data.
 * 
 * @param token the t_token of type rd to complete.
 * 
 * Alloc union u_data, then set rd data.
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

/** @brief set_rd - Alloc and fill redirect data.
 * 
 * @param token the t_token of type redir to complete.
 * 
 * Alloc rd file struct.
 * Get the next token str, set it as current redir filename.
 * Free the next WORD token.
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
	token->next = token->next->next;
	free_token(tmp);
	return (0);
}
