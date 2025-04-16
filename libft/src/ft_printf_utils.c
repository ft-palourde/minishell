/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:08:29 by rcochran          #+#    #+#             */
/*   Updated: 2025/01/21 14:07:00 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(int c);
void	ft_putstr(char *str);

void	ft_putchar(int c)
{
	ft_putchar_fd(c, 1);
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}
