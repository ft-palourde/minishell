/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:42 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/21 17:26:47 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_next_chunk(char *str);
char		*expand_chunk(char *str, t_ms *ms);
static void	skip_until_next_trigger(char *str, int *i);

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
	skip_until_next_trigger(str, &i);
	if (i - quote_type / 2)
	{
		free(new);
		new = ft_strndup(str + quote_type / 2, i - quote_type);
	}
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '~')
		{
			add_var_to_new(&new, str + i, ms);
			i++;
		}
		skip_until_next_trigger(str, &i);
	}
	return (new);
}

/** skip_until_next_trigger - Move forward in a string until precised character.
 * @str: The string to be read.
 * @i: The current index read.
 * 
 * This function browse the given string,
 * if it finds a $
 *
 * Returns: 
 */
static void	skip_until_next_trigger(char *str, int *i)
{
	(*i) += (str[*i] == '$' && (*i) != 0);
	while (str[*i] && str[*i] != '$' && str[*i] != '~')
		(*i)++;
}
