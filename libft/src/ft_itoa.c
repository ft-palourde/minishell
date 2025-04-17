/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:33:26 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/17 17:29:28 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_itoa(int n);
static	size_t			get_nb_len(unsigned int nb);
static size_t			get_size_to_malloc(int n);
static char				*putnbr_dest(int n, char *str);
static int				ft_check_nb_pow(unsigned int nb);

static int	ft_check_nb_pow(unsigned int nb)
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

static size_t	get_size_to_malloc(int n)
{
	size_t			size;
	size_t			nb_len;
	size_t			sign_size;
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		sign_size = 1;
	}
	else
	{
		nb = n;
		sign_size = 0;
	}
	nb_len = (size_t)get_nb_len(nb);
	size = 0;
	size = nb_len + sign_size + 1;
	return (size);
}

static	size_t	get_nb_len(unsigned int nb)
{
	size_t	nb_len;

	if (nb == 0)
		return (1);
	nb_len = 0;
	while (nb > 0)
	{
		nb_len++;
		nb /= 10;
	}
	return (nb_len);
}

static char	*putnbr_dest(int n, char *str)
{
	int				i;
	int				nb_pow;
	unsigned int	nb;

	i = 0;
	if (n >= 0)
		nb = n;
	else
	{
		str[i] = '-';
		nb = -n;
		i++;
	}
	nb_pow = ft_check_nb_pow(nb);
	while (nb_pow > 0)
	{
		str[i] = nb / nb_pow + '0';
		nb = nb % nb_pow;
		nb_pow = nb_pow / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;

	str = ft_calloc((get_size_to_malloc(n)), sizeof(char));
	if (!str)
		return (NULL);
	str = putnbr_dest(n, str);
	return (str);
}

/* int	main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("line 117 : error : un int est requis en arg");
		return (0);
	}
	printf("int %d -> string %s", atoi(av[1]), ft_itoa(atoi(av[1])));
	return (0);
} */
