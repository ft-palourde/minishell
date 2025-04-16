/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:30:14 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/15 16:53:51 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*tab;
	unsigned int	i;

	tab = NULL;
	i = 0;
	tab = malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!tab || s == NULL || f == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		tab[i] = f(i, (char)s[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
/* 
int	main(int ac, char **av)
{
	return (0);
}
 */