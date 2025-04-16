/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:52:59 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/18 16:52:04 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// The strchr() function returns a pointer to the first occurrence
//  of the character c in the string s.
// important : le modulo 256 car possiblement hors ascii (cf. UTF8)
char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	if (c == '\0')
		return ((char *) s + ft_strlen(s));
	while (*s && *s != (c % 256))
	{
		s++;
	}
	if (*s == (c % 256))
		return ((char *) s);
	return (NULL);
}

/* int	main(int ac, char **av)
{
	(void) ac;
	printf("strchr : %s \n", strchr(av[1], atoi(av[2])));
	printf("ft_strchr : %s \n", ft_strchr(av[1], atoi(av[2])));
	return (0);
} */