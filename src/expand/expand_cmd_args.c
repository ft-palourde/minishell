/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:18:57 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/14 14:29:58 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_args(t_cmd *cmd, t_ms *ms);
void	insert_arg_at(char ***args, int pos, const char *new_arg);

void	insert_content(int *i, char **args, char **split, char **new_arg)
{
	int		j;
	int		k;

	j = 0;
	k = 1;
	while (j < *i)
	{
		new_arg[j] = args[j];
		j++;
	}
	while (split[j - *i])
	{
		new_arg[j] = split[j - *i];
		j++;
	}
	while (args[*i + k])
	{
		new_arg[j] = args[*i + k];
		j++;
		k++;
	}
}

void	clear_empty_strings(char **new_arg)
{
	int	i;

	while (!new_arg[0][0])
	{
		i = 0;
		free(new_arg[0]);
		new_arg[0] = 0;
		while (new_arg[i + 1])
		{
			new_arg[i] = new_arg[i + 1];
			i++;
		}
	}
}

char	**insert_split(int *i, char **args, char **split)
{
	char	**new_arg;

	new_arg = ft_calloc(split_len(args) + split_len(split) + 1, sizeof(char *));
	if (!new_arg)
		return (perror("Minishell"), NULL);
	insert_content(i, args, split, new_arg);
	*i += split_len(split) - 1;
	free(args);
	free(split);
	return (new_arg);
}
/* 
insert split

malloc a split_len(args) + split_len(new_split) +1
je 

*/

char	**expand_split_handler(int *i, char **args, char *expanded)
{
	char	**new_split;

	if (check_quote_type(args[*i][0]))
	{
		new_split = ft_calloc(2, sizeof(char *));
		if (!new_split)
			return (perror("Minishell"), NULL);
		new_split[0] = expanded;
		if (!new_split[0])
			return (free(new_split), perror("Minishell"), NULL);
	}
	else
	{
		new_split = expand_split(expanded, ' ');
		if (!new_split)
			return (perror("Minishell"), NULL);
	}
	return (insert_split(i, args, new_split));
}

/**
 * @brief Expand all arguments of a command.
 *
 * Applies variable expansion to each argument in the command.
 *
 * @param cmd Pointer to the command to expand.
 * @param ms The minishell structure.
 */
void	expand_cmd_args(t_cmd *cmd, t_ms *ms)
{
	int		i;
	char	*expanded;

	i = 0;
	if (!cmd || !cmd->args)
		return ;
	while (cmd->args[i])
	{
		expanded = str_expand(cmd->args[i], ms);
		if (!expanded)
			return (perror("minishell"));
		cmd->args = expand_split_handler(&i, cmd->args, expanded);
		i++;
	}
	clear_empty_strings(cmd->args);
	return ;
}

/* 
Si la string est quoted
on expand le contenu et on execute normal
Sinon
	je split le contenu de l'expand
		protection
	je strjoin split[0] et args[i]
j'insert split[1] a split[n] entre args[i] et args[i + 1]
clear empty strings
*/


/* void	insert_expanded(char ***args, int *i, char *exp_arg)
{
	char	**split_args;
	int		count;
	int		j;
	int		is_quoted;

	is_quoted = check_quote_type((*args)[*i][0]);
	if (is_quoted)
	{
		free((*args)[*i]);
		(*args)[*i] = exp_arg;
		return ;
	}
	split_args = ft_split(exp_arg, ' ');
	if (!split_args)
	{
		free(exp_arg);
		perror("minishell");
		return ;
	}
	count = 0;
	while (split_args[count])
		count++;
	free((*args)[*i]);
	(*args)[*i] = ft_strdup(split_args[0]);
	if (!(*args)[*i])
	{
		free(exp_arg);
		free_split(split_args);
		perror("minishell");
		return ;
	}
	j = 1;
	while (j < count)
	{
		insert_arg_at(args, *i + j, split_args[j]);
		j++;
	}
	*i += count - 1;
	free(exp_arg);
	free_split(split_args);
}

void	insert_arg_at(char ***args, int pos, const char *new_arg)
{
	int		count;
	int		j;
	char	**new_args;

	count = 0;
	while ((*args)[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
	{
		perror("minishell");
		return ;
	}
	j = 0;
	while (j < pos)
	{
		new_args[j] = (*args)[j];
		j++;
	}
	new_args[pos] = ft_strdup(new_arg);
	if (!new_args[pos])
	{
		free(new_args);
		perror("minishell");
		return ;
	}
	while (j < count)
	{
		new_args[j + 1] = (*args)[j];
		j++;
	}
	new_args[count + 1] = NULL;
	free(*args);
	*args = new_args;
}


 */