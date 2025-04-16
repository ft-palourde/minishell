/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:16:31 by rcochran          #+#    #+#             */
/*   Updated: 2025/03/07 16:02:05 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
char	*convert_dec_in_new_base(int nbr, char *base);
int		is_base_valid(char *base);
int		ft_atoi_base(char *str, char *base);
int		is_in_base(char c, char *base);
size_t	get_num_len(int n, char *base);

int	is_base_valid(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if ((int)ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		while (base[i + j] != base[i])
		{
			if (base[i] == base[i + j])
				return (0);
			j++;
		}
		j = 1;
		i++;
	}
	if (base[i] == '\0')
		return (1);
	return (1);
}

char	*convert_dec_in_new_base(int nbr, char *base_to)
{
	unsigned int	n;
	unsigned int	base_len;
	char			*str;
	size_t			len;

	len = get_num_len(nbr, base_to);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str || is_base_valid(base_to) != 1)
		return (NULL);
	base_len = ft_strlen(base_to);
	if (nbr < 0)
	{
		n = -nbr;
		str[0] = '-';
	}
	else
		n = nbr;
	while (n > 0)
	{
		str[len--] = base_to[n % base_len];
		n /= base_len;
	}
	str[len] = base_to[n % base_len];
	return (str);
}

size_t	get_num_len(int n, char *base)
{
	size_t	len;
	size_t	base_len;
	size_t	num;

	len = 1;
	base_len = ft_strlen(base);
	if (n < 0)
	{
		len++;
		num = -n;
	}
	else
		num = n;
	while (num >= base_len)
	{
		num /= base_len;
		len++;
	}
	return (len);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		dec_num;
	char	*num_str;

	if (is_base_valid(base_from) == 0 || is_base_valid(base_to) == 0)
		return (NULL);
	dec_num = ft_atoi_base(nbr, base_from);
	num_str = convert_dec_in_new_base(dec_num, base_to);
	return (num_str);
}
