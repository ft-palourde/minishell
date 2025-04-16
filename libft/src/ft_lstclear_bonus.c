/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:16:58 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/21 19:19:07 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*tmp_next;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		tmp_next = current->next;
		ft_lstdelone(current, del);
		current = tmp_next;
	}
	*lst = NULL;
}
