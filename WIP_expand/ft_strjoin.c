/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:08:18 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/19 11:02:54 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_test.h"

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		str_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = NULL;
	str_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc ((size_t)(str_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

/* int	main(int ac, char **av)
{
	char	*str;

	if (ac != 3)
		return (0);
	str = ft_strjoin(av[1], av[2]);
	printf("La nouvelle string est : '%s'", str);
	free(str);
	return (0);
} */