/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:09:19 by rcochran          #+#    #+#             */
/*   Updated: 2025/05/26 16:00:11 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_word(t_token *token);

int	is_word(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == T_WORD)
		return (1);
	return (0);
}
