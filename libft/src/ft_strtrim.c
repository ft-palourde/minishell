/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:58:56 by rcochran          #+#    #+#             */
/*   Updated: 2024/11/20 19:37:07 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strtrim(char const *s1, char const *set);
static int			is_in_array(char c, const char *tab);

static int	is_in_array(char c, const char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	get_str_start(const char *s, const char *set)
{
	unsigned int	str_start;

	if (!s)
		return (0);
	str_start = 0;
	while (*s && is_in_array(s[str_start], set) == 1)
		str_start++;
	return (str_start);
}

static unsigned int	get_str_end(const char *s, const char *set)
{
	unsigned int	str_end;

	if (!s || ft_strlen(s) == 0)
		return (0);
	str_end = ft_strlen(s) - 1;
	while (*s && str_end > 0 && is_in_array(s[str_end], set) == 1)
		str_end--;
	return (str_end);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	str_start;
	unsigned int	str_end;
	size_t			str_len;
	char			*str;
	unsigned int	i;

	if (!s1 || s1 == NULL || s1 == 0)
		return (ft_strdup(""));
	str_start = get_str_start(s1, set);
	str_end = get_str_end(s1, set);
	if (str_start > str_end || (!str_start && !str_end))
		return (ft_strdup(""));
	str_len = (size_t)((str_end - str_start) + 1);
	str = malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = s1[str_start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

/* int	main(int ac, char **av)
{
	char	*cpy;

	cpy = ft_strtrim(av[1], av[2]);
	(void)ac;
	printf("res : %s", cpy);
	free(cpy);
	return (0);
} */