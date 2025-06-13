/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/12 17:18:42 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_next_chunk(char *str);
char		*expand_chunk(char *str, t_ms *ms);
static void	skip_until_dollar(char *str, int *i);

//recupere le prochain chunk quote ou pas
char	*get_next_chunk(char *str)
{
	int		i;
	char	*chunk;

	i = 0;
	if (str[0] == '\'' || str[0] == '\"')
		i = expand_is_closed(str, str[0]) + 1;
	else
	{
		while (str[i])
		{
			if ((str[i] == '\'' || str[i] == '\"') && !is_escaped(str, i))
				break ;
			i++;
		}
	}
	chunk = ft_strndup(str, i);
	return (chunk);
}

/* ressort le chunk trimed de ses quotes
avec ses variables remplacees par leur valeur */
char	*expand_chunk(char *str, t_ms *ms)
{
	char	*new;
	int		quote_type;
	int		i;

	i = 0;
	quote_type = check_quote_type(str[0]);
	if (quote_type == 1)
		return (ft_strndup(str + 1, ft_strlen(str) - 2));
	new = ft_strdup("");
	skip_until_dollar(str, &i);
	if (i - quote_type / 2)
	{
		free(new);
		new = ft_strndup(str + quote_type / 2, i - quote_type);
	}
	while (str[i])
	{
		if (str[i] == '$')
		{
			add_var_to_new(&new, str + i, ms);
			i++;
		}
		skip_until_dollar(str, &i);
	}
	return (new);
}

static void	skip_until_dollar(char *str, int *i)
{
	while (str[*i] && str[*i] != '$')
		(*i)++;
}
