/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:36:23 by rcochran          #+#    #+#             */
/*   Updated: 2025/01/21 14:03:37 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_nbr(int nb);
int		ft_print_usnbr(unsigned long nb);
char	*ft_uitoa(unsigned long nb);
int		ft_check_nb_pow(unsigned int nb);

int	ft_print_nbr(int nb)
{
	int		nb_len;
	char	*nb_str;

	if (nb == 0)
		return (ft_print_char('0'));
	nb_str = ft_itoa(nb);
	nb_len = ft_print_str(nb_str);
	free(nb_str);
	return (nb_len);
}

int	ft_print_usnbr(unsigned long usnb)
{
	int		usnb_len;
	char	*usnb_str;

	usnb_len = 0;
	if (usnb == 0)
		return (ft_print_char('0'));
	usnb_str = ft_uitoa(usnb);
	usnb_len = ft_print_str(usnb_str);
	free(usnb_str);
	return (usnb_len);
}

int	ft_check_nb_pow(unsigned int nb)
{
	int	nb_pow;

	nb_pow = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		nb_pow = nb_pow * 10;
	}
	return (nb_pow);
}

char	*ft_uitoa(unsigned long nb)
{
	char			*nb_str;
	int				nb_len;
	unsigned long	i;
	int				nb_pow;

	i = nb;
	nb_len = 0;
	while (i > 0)
	{
		nb_len++;
		i /= 10;
	}
	i = 0;
	nb_str = (char *)ft_calloc(nb_len + 1, sizeof(char));
	if (!nb_str)
		return (NULL);
	nb_pow = ft_check_nb_pow(nb);
	while (nb_pow != 0)
	{
		nb_str[i] = nb / nb_pow + '0';
		nb = nb % nb_pow;
		nb_pow = nb_pow / 10;
		i++;
	}
	return (nb_str);
}
