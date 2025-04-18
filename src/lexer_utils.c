/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:44:34 by rcochran          #+#    #+#             */
/*   Updated: 2025/04/18 18:36:03 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_space(char c);

// char	*handle_quotes(char *input, int i);

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}

/* char	*handle_quotes(char *input, int i)
{
	char	*str;
	char	limiter;
	size_t	len;

	limiter = input[i];
	i++;
	while (input[i] && input[i]  != limiter)
	{
		len++;
		i++;
	}
	// str = ft_substr();
	return (str);
} */
/* // checks if the quote, double quote or parenthesis has a closing occurence
// returns adress if found, NULL otherwise
int	is_closed(char *s, char c)
{
	int		i;

	i = 1;
	if (c == '(')
		c = ')';
	while (s[i] != c && s[i])
		i++;
	if (s[i])
		return (i);
	return (0);
}

static int	get_split_len(char const *s, char c)
{
	int	i;
	int	to_close;

	i = 0;
	while (*(char *)s != c && *(char *)s)
	{
		if ((*(char *)s == '"' || *(char *)s == '\'' || *(char *)s == '(') \
										&& is_closed((char *)s + i, *(char *)s))
		{
			to_close = is_closed((char *)s + i, *(char *)s);
			s = s + to_close;
			i = i + to_close;
		}
		s++;
		i++;
	}
	return (i);
}

static void	get_split_count_word(char const *s, char c, int *count)
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
											&& is_closed((char *)s + i, s[i]))
				i += is_closed((char *)s + i, s[i]);
			i++;
		}
	}
}

char	**one_split(const char *s)
{
	char	**split;

	split = ft_calloc(2, sizeof (char *));
	if (!split)
		return (NULL);
	split[0] = ft_strdup(s);
	return (split);
}

char	**custom_split(char const *s, char c)
{
	char	**str;
	int		count;
	int		i;

	i = 0;
	count = 0;
	get_split_count_word(s, c, &count);
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
		str[i] = ft_strldup((char *)s, get_split_len(s, c));
		if (!(str[i]))
			return (clear_split(str), NULL);
		i++;
		s += get_split_len(s, c);
	}
	return (str);
} */
