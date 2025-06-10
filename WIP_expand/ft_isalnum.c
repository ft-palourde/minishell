/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:34:31 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/13 15:32:25 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_test.h"

int	ft_isalnum(int c);

int	ft_isalnum(int c)
{
	int	is_alnum;

	is_alnum = 1;
	if (!(c >= 65 && c <= 90)
		&& !(c >= 97 && c <= 122)
		&& !(c >= 48 && c <= 57))
	{
		is_alnum = 0;
	}
	return (is_alnum);
}
