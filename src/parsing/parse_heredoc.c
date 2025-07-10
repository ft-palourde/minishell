/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/10 18:06:01 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parse_heredoc(t_token *token);
static int	set_hd(t_token *token);

/** @brief parse_heredoc - Alloc and fill heredoc data.
 * 
 * @param token the t_token of type heredoc to complete.
 * 
 * Alloc union u_data, then set rd data.
 */
int	parse_heredoc(t_token *token)
{
	if (!token || token->type != T_HEREDOC)
		return (1);
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return (1);
	token->data->rd = malloc(sizeof(t_rd));
	if (!token->data->rd)
	{
		free(token->data);
		token->data = NULL;
		return (1);
	}
	return (set_hd(token));
}

/** @brief set_hd - Fills token rd data with heredoc data.
 * 
 * @param token the t_token of type HEREDOC to complete.
 * 
 * Set the next token str as heredoc limiter.
 * Free the next token.
 */
static int	set_hd(t_token *token)
{
	t_token	*tmp;

	token->data->rd->heredoc = malloc(sizeof(t_rd_heredoc));
	if (!token->data->rd->heredoc)
	{
		free(token->data->rd);
		token->data->rd = NULL;
		return (1);
	}
	token->data->rd->heredoc->lim = ft_strdup(token->next->str);
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
