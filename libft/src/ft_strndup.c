/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:28 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/21 11:11:51 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n);

char	*ft_strndup(const char *s, int n)
{
	int		s_len;
	int		i;
	char	*dest;

	i = 0;
	s_len = 0;
	while (s[s_len])
		s_len++;
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
