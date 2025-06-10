/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:14:41 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 12:09:13 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_test.h"

/* char	*get_home(char **env)
{
	char	*home;
	int		i;

	i = 0;
	while (env[i] && strncmp(env[i], "HOME=", 5))
		i++;
	if (!env[i])
		return (ft_putstr_fd("cd : HOME not set\n", 2), NULL);
	home = get_var_value(env[i]);
	if (!home)
		return (perror("malloc"), NULL);
	return (home);
} */

// faire une fonction char	*get_var() qui reprend la logique gethome pour toute variable

char	*get_var_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] != '=')
		i++;
	value = ft_strdup(var + i + 1);
	if (!value)
		return (perror("malloc"), NULL);
	return (value);
}

char	*var_name_to_value(char *name, char **env)
{
	int		i;
	int		len;
	char	*value;

	len = ft_strlen(name);
	i = 0;
	value = NULL;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], len) && env[i][len] == '=')
			break ;
		i++;
	}
	if (env[i])
	{
		value = get_var_value(env[i]);
		if (!value)
			return (perror("malloc"), NULL);
	}
	return (value);
}

/** var_expand - Expands a variable in the given string.
 * @str: The string containing the variable to expand.
 * @env: The grid of environment variables.
 * 
 * This function checks if the string starts with a '$' character,
 * extracts the variable name, retrieves its value, and constructs
 * a new string with the expanded value.
 *
 * Returns: A newly allocated string with the expanded variable,
 * or NULL on failure.
 */

char	*var_expand(char *str, char **env)
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
	var_value = var_name_to_value(var_name, env);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	expanded_str = ft_strjoin(var_value, str + i);
	free(var_value);
	return (expanded_str);
}

char	*expand_chunk(char *str, char **env)
{
	char	*new;
	char	*var;
	char	*tmp;
	int 	quote_type; //0(none) 1(simple) ou 2(double)
	int		i;

	check_quote_type(); "dkjdaksd$TOTO"
	new = trim_quotes(); dkjdaksd
	if (quote_type == 1)
		return (trim_quotes(str));
	//if (on commence pas par un dollar)
	//	sortir une string de tout le debug jusqu'au dollar ou end
	while (str[i])
	{
		if (str[i] == '$')
		{
			var = var_expand(str + i, env);
			tmp = new;
			new = ft_strjoin(new, var);
			free(tmp);
		}
		while (str[i] && str[i] != '$')
				i++;
		i++;
	}
}
//prend une string a expand et la return en ayant remplace les var d'env
char	*str_expand(char *str, char **env)
{
	char	*new;
	char 	*tmp;
	char	*chunk;
	int		i;

	new = ft_strdup("");
	//while str[i]
		chunk = get_next_chunk(str, i, env); //recupere le prochain chunk quote ou pas
		i += ft_strlen(chunk);
		chunk = expand_chunk(chunk); //ressort le chunk trimed de ses quotes et avec ses variables remplacees par leur valeur
		tmp = new;
		new = ft_strjoin(new, chunk);
		free(tmp);
		free(chunk);
		if (!new)
			return (NULL);
}