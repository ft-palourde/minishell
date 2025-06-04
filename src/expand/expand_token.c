/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:49:16 by rcochran          #+#    #+#             */
/*   Updated: 2025/06/04 10:22:45 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_token(t_token *token);
char	*expand_variable(char *str);
char	*get_env_value(char var_name);
char	*expand_path(char *arg);
/* 
#include "minishell.h"

void	expand(t_token *token);
void	expand_variable(char *str);
char	*get_env_value(char var_name);
char	*expand_path(char *arg);
 */

/*
différents cas d'expand :  
- path
- variables
*/


// entre simple quotes trim quotes et c'est tout
// entre double quotes trim quotes et expand

void	expand_token(t_token *token)
{
	int		i;
	char	**args;


	//expand filename sur token rd
	// ne pas expand * si c'est échappé par quotes
	i = 0;
	if (!token || (token->type != T_CMD && token->type != T_WORD))
		return ;
	if (token->data && token->data->cmd && token->data->cmd->args)
	{
		args = token->data->cmd->args;
		while (args[i])
		{
			if (args[i][0] == '\0')
				i++;
			expand_variable(args[i]);
			// if (ft_strchr(args[i], '*') || ft_strchr(args[i], './'))
			// expand_path(args[i]);
			if (ft_strchr(args[i], '*'))
				expand_globbing();
			i++;
		}
	}
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
/* 
expand_path()
expands globbing patterns in the given string.
*/

/* 
expand_path
*/

// entre simple quotes trim quotes et c'est tout
// entre double quotes trim quotes et expand

/*
différents cas d'expand :  
- path
- variables
*/

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