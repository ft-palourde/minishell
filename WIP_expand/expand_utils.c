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

char	*get_next_chunk();
char	*trim_quotes(char *str);
int	check_quote_type(char c);
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



// abcdef$TOTO$TOTO


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
	int		quote_type;
	int		i;

	quote_type = check_quote_type(str[0]);
	if (quote_type == 1)
		return (ft_strndup(str + 1, ft_strlen(str - 2)));
	new = ft_strdup("");
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (i - quote_type / 2)
		{
			new = ft_strndup(str + quote_type / 2, i - quote_type / 2);
			i++;
		}
		if (str[i] == '$')
		{
			add_var_to_new(var, &new, str + i, env);
		}
		while (str[i] && str[i] != '$')
				i++;
	}
	return (new);
}

void	add_var_to_new(char *var, char **new, char *str, char **env)
{
	char	*tmp;

	var = var_expand(str, env);
	tmp = *new;
	*new = ft_strjoin(*new, var);
	free(tmp);
	free(var);
}

int	check_quote_type(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
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
		chunk = expand_chunk(chunk, env); //ressort le chunk trimed de ses quotes et avec ses variables remplacees par leur valeur
		tmp = new;
		new = ft_strjoin(new, chunk);
		free(tmp);
		free(chunk);
		if (!new)
			return (NULL);
		return (new);
}

char	*get_next_chunk(char *str, int len)
{
	//si quote : return toute 
	int 	i;
	char	*chunk;

	
	return (NULL);
}

/* 
return the length of current word
*/
int	extract_word_len(const char *input)
{
	int	i;
	int	quote_len;

	i = 0;
	quote_len = 0;
	while (input[i] && !is_space(input[i]) && !is_operator(*(input + i)))
	{
		quote_len = is_closed((char *)input + i, input[i]);
		if ((input[i] == '"' || input[i] == '\'') && quote_len)
		{
			i += quote_len + 1;
		}
		else
			i++;
	}
	return (i);
}

/*
checks if the quote, double quote or parenthesis has a closing occurence
returns the number of char read if found, 0 otherwise
*/
int	is_closed(char *str, char c)
{
	int		i;

	i = 1;
	if (c == '(')
		c = ')';
	while (str[i] != c && str[i])
		i++;
	if (str[i] && is_escaped(str, i))
		return (i);
	return (0);
}

int	is_backslash(char c)
{
	return (c == '\\');
}

int	is_escaped(char *input, int index)
{
	int	is_escaped;

	is_escaped = 0;
	index--;
	while (index >= 0 && is_backslash(input[index]))
	{
		is_escaped++;
		index--;
	}
	return (is_escaped % 2);
}