/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:35:19 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/02 16:52:42 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}
