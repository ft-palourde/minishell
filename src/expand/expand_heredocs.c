/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:19:06 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/21 17:46:24 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hd_var_expand(char *str, t_ms *ms)
{
	char	*var_value;
	char	*var_name;
	int		i;

	if (!str || str[0] != '$')
		return (ft_strdup(str));
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	var_value = var_name_to_value(var_name, ms);
	free(var_name);
	return (var_value);
}

void	hd_add_var_to_new(char **new, char *str, t_ms *ms)
{
	char	*tmp;
	char	*var;

	var = hd_var_expand(str, ms);
	tmp = *new;
	*new = ft_strjoin(*new, var);
	free(tmp);
	free(var);
}

int	add_quote_to_new(char quote, char **new)
{
	char	*tmp;
	char	*c;

	c = ft_calloc(sizeof(char), 2);
	if (!c)
		return (perror("malloc"), 1);
	c[0] = quote;
	tmp = *new;
	*new = ft_strjoin(*new, c);
	free(tmp);
	if (!*new)
		perror("malloc");
	return (1);
}

char	*hd_expand_chunk(char *str, t_ms *ms)
{
	char	*new;
	int		i;
	int		quote;

	quote = (str[0] == '\'' || str[0] == '\"');
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	new = ft_strndup(str, i);
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '~')
		{
			hd_add_var_to_new(&new, str + i, ms);
			i++;
		}
		while (str[i] && str[i] != '$')
			i++;
	}
	if (quote)
		add_quote_to_new(str[0], &new);
	return (new);
}

char	*hd_expand(t_ms *ms, char *str)
{
	char	*new;
	char	*tmp;
	char	*chunk;
	int		i;

	i = 0;
	new = ft_strdup("");
	while (str && str[i])
	{
		chunk = get_next_chunk(str + i);
		i += ft_strlen(chunk);
		tmp = chunk;
		chunk = hd_expand_chunk(chunk, ms);
		free(tmp);
		tmp = new;
		new = ft_strjoin(new, chunk);
		free(tmp);
		free(chunk);
		if (!new)
			return (NULL);
	}
	return (new);
	return (new);
}
