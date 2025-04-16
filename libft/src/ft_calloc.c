/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:18:45 by rcochran          #+#    #+#             */
/*   Updated: 2025/02/17 11:53:51 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size);
/* attention a la size max */

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	ptr = 0;
	if (nmemb <= 0 || size <= 0)
	{
		return (malloc(0));
	}
	if ((nmemb * size) > 2147483647 || SIZE_MAX / size <= nmemb)
	{
		return (0);
	}
	ptr = malloc(sizeof(char) * nmemb * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, (size * nmemb));
	return ((void *)ptr);
}
/*
#include<stdio.h>

int	main(void)
{
	void	*buf;

	size_t	nelem;
	size_t	s;
	char	*dest;

	nelem = 1073741824;
	s = 1073741824;
	buf = malloc(s * nelem);
	if (buf == NULL)
	{
		printf("NULL");
	}
	else
	{
		printf("else");
	}
	dest = ft_calloc(nelem, s);
	free(buf);
	free(dest);
	return (0);
}*/