/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:28 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/03 12:17:53 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n);

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*dest;

	i = 0;
	if (!s)
		return (NULL);
	if (n < 0)
		return (NULL);
	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
