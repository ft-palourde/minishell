/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:22:38 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/22 14:44:16 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t			strlcat(char *dst, const char *src, size_t siz);
/* size_t strlcat (char * dst, const char * src, size_t siz)
		Concatenate two strings. Appends src to string dst of size siz (unlike
		strncat(), siz is the full size of dst, not space left). At most siz-1
		characters will be copied. Always NULL terminates (unless siz <=
		strlen(dst)).

		Returns
			The strlcat() function returns strlen(src) + MIN(siz,
			strlen(initial dst)). If retval >= siz, truncation occurred.

		Appends src to string dst of size siz (unlike strncat(), siz is the
		full size of dst, not space left). At most siz-1 characters will be
		copied. Always NULL terminates (unless siz <= strlen(dst)).

		Returns
			The strlcat() function returns strlen(src) + MIN(siz,
			strlen(initial dst)). If retval >= siz, truncation occurred.
 */
size_t	ft_strlcat(char *dest, const char *src, size_t size);

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	if (size <= ft_strlen(dest))
		return (ft_strlen((char *)src) + size);
	while (src[j] && (i + j) < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (ft_strlen((char *)src) + i);
}
