/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:17 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 14:30:54 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
return the var part after "=" sign
*/
/* char	*get_var_value(char *var)
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
} */

/*
epand_variable()
expands environment variables in the given string.
*/

/* 
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
 */

void	expand_variable(t_token *token, char **env)
{
	char	**args;
	int		i;

	if (!token || !token->data || !token->data->cmd || !token->data->cmd->args)
		return ;
	args = token->data->cmd->args;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\0')
		{
			i++;
			continue ;
		}
		args[i] = str_expand(args[i], env);
		if (ft_strchr(args[i], '*'))
			expand_globbing(args[i]);
		i++;
	}
}

/** str_expand - Expands a variable in the given string.
 * @str: The string containing the variable to expand.
 *
 * This function checks if the string starts with a '$' character,
 * extracts the variable name, retrieves its value, and constructs
 * a new string with the expanded value.
 *
 * Returns: A newly allocated string with the expanded variable,
 * or NULL on failure.
 */
char	*str_expand(char *str, char **env)
{
	char	*expanded_str;
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
	var_value = get_var_value(var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	expanded_str = ft_strjoin(var_value, str + i);
	free(var_value);
	return (expanded_str);
}
