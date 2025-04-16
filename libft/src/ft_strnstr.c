/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:09:27 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/20 18:15:18 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	if (len < 1)
		return (0);
	if (ft_strlen((char *)little) > ft_strlen((char *)big) || *big == '\0')
		return (NULL);
	while (big[i] && i < len)
	{
		while (big[i + j] && little[j]
			&& little[j] == big[i + j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		j = 0;
		i++;
	}
	return (NULL);
}

/* int	main(int ac, char **av)
{
	(void)ac;
	printf("ft_strnstr : %s\n", ft_strnstr(av[1], av[2], (size_t)atoi(av[3])));
	printf("strnstr : %s\n", strnstr(av[1], av[2], (size_t)atoi(av[3])));
	return (0);
} */