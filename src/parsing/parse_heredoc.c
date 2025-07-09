/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/09 16:50:26 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_heredoc(t_token *token);
static void	set_hd(t_token *token);

/** @brief parse_heredoc - Alloc and fill heredoc data.
 * 
 * @param token the t_token of type heredoc to complete.
 * 
 * Alloc union u_data, then set rd data.
 */
void	parse_heredoc(t_token *token)
{
	if (!token || token->type != T_HEREDOC)
		return ;
	token->data = malloc(sizeof(union u_data));
	if (!token->data)
		return ;
	token->data->rd = malloc(sizeof(t_rd));
	if (!token->data->rd)
	{
		free(token->data);
		token->data = NULL;
		return ;
	}
	set_hd(token);
	return ;
}

/** @brief set_hd - Fills token rd data with heredoc data.
 * 
 * @param token the t_token of type HEREDOC to complete.
 * 
 * Set the next token str as heredoc limiter.
 * Free the next token.
 */
static void	set_hd(t_token *token)
{
	t_token	*tmp;

	token->data->rd->heredoc = malloc(sizeof(t_rd_heredoc));
	if (!token->data->rd->heredoc)
	{
		free(token->data->rd);
		token->data->rd = NULL;
		return ;
	}
	token->data->rd->heredoc->lim = ft_strdup(token->next->str);
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
