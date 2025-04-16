/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:42:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/01/21 14:03:40 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_hex_fmt(unsigned long nb, char c);
int		ft_putnbr_hexbase(unsigned long nb, char *hex_base);
int		get_hex_nb_len(unsigned long nb);

int	get_hex_nb_len(unsigned long nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

int	ft_print_hex_fmt(unsigned long nb, char c)
{
	int		len;
	char	*hex_base_lower;
	char	*hex_base_upper;

	hex_base_lower = "0123456789abcdef";
	hex_base_upper = "0123456789ABCDEF";
	if (nb == 0)
	{
		return (ft_print_char('0'));
	}
	len = 0;
	if (c == 'X')
		len += ft_putnbr_hexbase(nb, hex_base_upper);
	else
		len += ft_putnbr_hexbase(nb, hex_base_lower);
	return (len);
}

int	ft_putnbr_hexbase(unsigned long nb, char *hex_base)
{
	unsigned int	base_len;
	int				nb_len;

	nb_len = 0;
	nb_len = get_hex_nb_len(nb);
	base_len = (int)ft_strlen(hex_base);
	if (nb >= base_len)
	{
		ft_putnbr_hexbase(nb / base_len, hex_base);
	}
	ft_print_char(hex_base[nb % base_len]);
	return (nb_len);
}
