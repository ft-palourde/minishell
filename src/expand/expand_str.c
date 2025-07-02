/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:03 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/25 15:35:57 by rcochran         ###   ########.fr       */
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
		perror("malloc");
	while (str && str[i])
	{
		chunk = get_next_chunk(str + i);
		i += ft_strlen(chunk);
		tmp = chunk;
		chunk = expand_chunk(chunk, ms);
		free(tmp);
		tmp = new;
		new = ft_strjoin(new, chunk);
		free(tmp);
		free(chunk);
		if (!new)
			return (NULL);
	}
	return (new);
}
