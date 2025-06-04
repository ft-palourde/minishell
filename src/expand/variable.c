/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 10:23:28 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
return the var part after "=" sign
*/
char	*get_var_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] != '=')
		i++;
	value = ft_strdup(var + i);
	if (!value)
		return (perror("malloc"), NULL);
	return (value);
}

/*
epand_variable()
expands environment variables in the given string.
*/
char	*expand_variable(char *str)
{
	char	*expanded_str;
	char	*var_value;
	char	*var_name;
	int		i;

	// verification du type de quotes
	// if simple quotes avancer de retval is_closed char
	if (!str || str[0] != '$')
		return ;
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, 1, i - 1);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	expanded_str = ft_strjoin(var_value, str + i);
	free(var_value);
	return (expanded_str);
}
