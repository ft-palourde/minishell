/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:18:19 by rcochran          #+#    #+#             */
/*   Updated: 2025/01/21 14:03:19 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_ptr(unsigned long ptr);

int	ft_print_ptr(unsigned long ptr)
{
	int		len;

	len = 0;
	if (ptr == 0)
		return (ft_print_str("(nil)"));
	len = ft_print_str("0x");
	len += ft_print_hex_fmt(ptr, 'x');
	return (len);
}
