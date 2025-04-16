/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:15:13 by rcochran          #+#    #+#             */
/*   Updated: 2025/01/21 14:03:32 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...);
int	ft_case_by_format(va_list ptr, char c);
int	ft_print_char(int c);
int	ft_print_str(char *str);

int	ft_print_char(int c)
{
	ft_putchar(c);
	return (1);
}

int	ft_print_str(char *str)
{
	if (!str)
		return (ft_print_str("(null)"));
	return (ft_putstr(str), (int)ft_strlen(str));
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	ptr;
	int		len;

	i = 0;
	len = 0;
	va_start(ptr, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			len += ft_case_by_format(ptr, str[i + 1]);
			i++;
		}
		else
		{
			len += ft_print_char(str[i]);
		}
		i++;
	}
	va_end(ptr);
	return (len);
}

int	ft_case_by_format(va_list ptr, char c)
{
	if (c == 'c')
		return (ft_print_char(va_arg(ptr, int)));
	else if (c == 's')
		return (ft_print_str(va_arg(ptr, char *)));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(ptr, unsigned long)));
	else if (c == 'd' || c == 'i')
		return (ft_print_nbr(va_arg(ptr, int)));
	else if (c == 'u')
		return (ft_print_usnbr(va_arg(ptr, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_print_hex_fmt(va_arg(ptr, unsigned int), c));
	else if (c == '%')
		return (ft_print_char(37));
	return (0);
}
