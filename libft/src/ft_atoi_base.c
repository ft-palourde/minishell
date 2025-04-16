/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:41:56 by rcochran          #+#    #+#             */
/*   Updated: 2025/03/07 15:57:21 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_base(char c, char *base);
int	ft_atoi_base(char *str, char *base);

/* returns a num(int) in base 10 from num(str) in any valid base specified*/
int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		sign;
	int		num;
	size_t	base_len;

	base_len = ft_strlen(base);
	if (is_base_valid(base) != 1)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\v' || str[i] == '\r')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && is_in_base(str[i], base))
	{
		num = num * (int)base_len + (ft_strchr(base, str[i]) - base);
		i++;
	}
	return (num * sign);
}

int	is_in_base(char c, char *base)
{
	return (ft_strchr(base, c) != NULL);
}
