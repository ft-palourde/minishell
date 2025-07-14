/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:05:41 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/14 17:05:44 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_is_closed(char *s, char c)
{
	int		i;

	i = 1;
	while (s[i] != c && s[i])
		i++;
	if (s[i])
		return (i);
	return (0);
}

static int	expand_split_len(char const *s, char c)
{
	int	i;
	int	to_close;

	i = 0;
	while (*(char *)s != c && *(char *)s)
	{
		if ((*(char *)s == '"' || *(char *)s == '\'' || *(char *)s == '(') \
			&& quote_is_closed((char *)s + i, *(char *)s))
		{
			to_close = quote_is_closed((char *)s + i, *(char *)s);
			s = s + to_close;
			i = i + to_close;
		}
		s++;
		i++;
	}
	return (i);
}

static void	expand_count_word(char const *s, char c, int *count)
{
	int	i;

	i = 0;
	if (s[0] == '\0')
		return ;
	if (s[0] != c)
		*count = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i])
				*count = *count + 1;
		}
		while (s[i] && s[i] != c)
		{
			if ((s[i] == '"' || s[i] == '\'' || s[i] == '(') \
					&& quote_is_closed((char *)s + i, s[i]))
				i += quote_is_closed((char *)s + i, s[i]);
			i++;
		}
	}
}

static char	**one_split(const char *s)
{
	char	**split;

	split = ft_calloc(2, sizeof (char *));
	if (!split)
		return (NULL);
	split[0] = ft_strdup(s);
	return (split);
}

char	**expand_split(char const *s, char c)
{
	char	**str;
	int		count;
	int		i;

	i = 0;
	count = 0;
	expand_count_word(s, c, &count);
	if (!count)
		return (one_split(s));
	str = 0;
	str = ft_calloc(count + 1, sizeof (char **));
	if (!(str))
		return (0);
	while (count > i)
	{
		while (*(char *)s == c)
			s++;
		str[i] = ft_strndup((char *)s, expand_split_len(s, c));
		if (!(str[i]))
			return (free_split(str), NULL);
		i++;
		s += expand_split_len(s, c);
	}
	return (str);
}