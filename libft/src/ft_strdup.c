/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:18:55 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/20 17:46:30 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s);

char	*ft_strdup(const char *s)
{
	int		s_len;
	int		i;
	char	*dest;

	i = 0;
	s_len = 0;
	while (s[s_len])
		s_len++;
	dest = malloc(sizeof(char) * (s_len + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* int	main(int ac, char **av)
{
	char	*cpy;
	// if (ac < 2)
	// 	return (0);
	(void)ac;
	(void)av;
	cpy = ft_strdup(0);
	printf("la copie de 0 est %s", cpy);
	free(cpy);
	return (0);
} */
