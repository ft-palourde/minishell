/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:23:33 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/20 18:05:50 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if ((!src && !dest) || !n)
		return ((void *)dest);
	i = 0;
	while (i < n)
	{
		*(unsigned char *) dest = *(unsigned char *) src;
		dest++;
		src++;
		i++;
	}
	return ((void *)dest - i);
}

/* 
int	main(int ac, char **av)
{
	(void) ac;
	char	*dest = av[1];
	char	*src = av[2];
	size_t	n =(size_t)atoi(av[3]);
	// printf("test 1 memcpy() : %s\n", (char *)memcpy(dest, src, n));
	printf("test 2 : ft_memcpy() : %s\n", (char *)ft_memcpy(dest, src, n));

}
*/
