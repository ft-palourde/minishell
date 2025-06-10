/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:54:01 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/18 17:21:47 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_test.h"

char	*ft_strrchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (i > 0 && s[i] != (c % 256))
	{
		i--;
	}
	if (s[i] != (c % 256))
		return (0);
	else
		return ((char *) &s[i]);
}
