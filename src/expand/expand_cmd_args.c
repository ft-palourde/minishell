/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:18:57 by rcochran          #+#    #+#             */
/*   Updated: 2025/07/11 14:00:05 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd_args(t_cmd **cmd, t_ms *ms);
void	insert_expanded(char ***args, int *i, char *exp_arg);
void	insert_arg_at(char ***args, int pos, const char *new_arg);

/**
 * @brief Expand all arguments of a command.
 *
 * Applies variable expansion to each argument in the command.
 *
 * @param cmd Pointer to the command to expand.
 * @param ms The minishell structure.
 */
void	expand_cmd_args(t_cmd **cmd, t_ms *ms)
{
	int		i;
	char	*tmp;
	t_cmd	*cmd_to_expand;
	char	*sdup;

	cmd_to_expand = (*cmd);
	i = 0;
	if (!cmd_to_expand || !cmd_to_expand->args)
		return ;
	while (cmd_to_expand->args[i])
	{
		tmp = str_expand(cmd_to_expand->args[i], ms);
		if (!tmp)
			return (perror("minishell"));
		sdup = ft_strdup(tmp);
		if (!sdup)
		{
			free(tmp);
			return (perror("minishell"));
		}
		insert_expanded(&cmd_to_expand->args, &i, sdup);
		free(tmp);
	}
	return ;
}

void	insert_expanded(char ***args, int *i, char *exp_arg)
{
	char	**split_args;
	int		count;
	int		j;

	if (check_quote_type((*args)[*i][0]))
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
	int		count = 0;
	int		j;
	char	**new_args;

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

