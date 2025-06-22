/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:24:51 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 12:30:54 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	while (env[i] && env[i][j] && env[i][j] != '=')
		j++;
	if (!env[i] || !env[i][j] || env[i][j] != '=')
		return (ft_split("", '\0'));
	j++;
	return (ft_split(env[i] + j, ':'));
}

int	cmd_exists(char *cmd, char *path)
{
	char	*join;
	char	*join2;

	join = ft_strjoin(path, "/");
	if (!join)
		return (-1);
	join2 = ft_strjoin(join, cmd);
	if (!join2)
		return (free(join), -1);
	if (!access(join2, F_OK))
		if (!access(join2, X_OK))
			return (free(join), free(join2), 1);
	free(join);
	free(join2);
	return (0);
}

char	*add_paths(char *p1, char *p2)
{
	char	*new;
	char	*tmp;

	if (!p1 && !p2)
		return (NULL);
	if (!p1)
		return (p2);
	if (!p2)
		return (p1);
	new = ft_strjoin(p1, "/");
	if (!new)
		return (perror("malloc"), NULL);
	tmp = new;
	new = ft_strjoin(tmp, p2);
	free(tmp);
	return (new);
}

char	*get_cmd_path(t_cmd *cmd, char **paths)
{
	int		i;
	int		found;
	char	*not_found;

	i = 0;
	found = 0;
	cmd->path = cmd->args[0];
	if (!cmd->path)
		return (perror("malloc"), NULL);
	while (paths[i])
	{
		found = cmd_exists(cmd->path, paths[i]);
		if (found == -1)
			return (0);
		else if (found)
			return (add_paths(paths[i], cmd->path));
		i++;
	}
	not_found = ft_strdup(cmd->path);
	if (!not_found)
		perror("malloc");
	return (not_found);
}

int	init_cmd(t_tree *node, t_ms *ms)
{
	char	**paths;
	t_cmd	*cmd;

	cmd = node->token->data->cmd;
	expand_cmd_args(&cmd, ms);
	if (!is_builtin(node->token))
	{
		if (is_absolute(cmd->args[0]))
			cmd->path = ft_strdup(cmd->args[0]);
		else
		{
			paths = get_paths(ms->env);
			if (!paths)
				return (1);
			cmd->path = get_cmd_path(node->token->data->cmd, paths);
			reverse_cascade_free(paths, split_len(paths));
		}
		if (!cmd->path)
			return (perror("malloc"), 1);
	}
	if (ms->file_in != STDIN_FILENO)
		node->token->in_fd = ms->file_in;
	if (ms->file_out != STDOUT_FILENO)
		node->token->out_fd = ms->file_out;
	return (0);
}
