/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:03 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/04 11:38:32 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_expand(char *str, t_ms *ms);

char	*str_expand(char *str, t_ms *ms)
{
	char	*new;
	char	*tmp;
	char	*chunk;
	int		i;

	i = 0;
	new = ft_strdup("");
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		chunk = get_next_chunk(str + i);
		if (!chunk)
			return (free(new), NULL);
		i += ft_strlen(chunk);
		tmp = chunk;
		chunk = expand_chunk(chunk, ms);
		if (!chunk)
			return (free(tmp), NULL);
		free(tmp);
		tmp = new;
		new = ft_strjoin(tmp, chunk);
		if (!new)
			return (free(tmp), free(chunk), NULL);
		free(tmp);
		free(chunk);
	}
	return (new);
}
