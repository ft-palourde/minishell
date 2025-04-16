/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:15:58 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/07 10:11:04 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	new_ptr = ft_calloc(1, size);
	if (!new_ptr)
		return (NULL);
	ft_memmove(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
