/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:17:32 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/20 18:10:10 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size);

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size != 0)
	{
		i = 0;
		while (src[i] && i < size - 1)
		{
			dest[i] = (char)src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
