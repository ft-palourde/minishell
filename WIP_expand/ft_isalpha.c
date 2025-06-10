/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:34:17 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/13 15:32:41 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_test.h"

int	ft_isalpha(int c);

int	ft_isalpha(int c)
{
	int	is_alpha;

	is_alpha = 1;
	if (!(c >= 65 && c <= 90)
		&& !(c >= 97 && c <= 122))
	{
		is_alpha = 0;
	}
	return (is_alpha);
}
