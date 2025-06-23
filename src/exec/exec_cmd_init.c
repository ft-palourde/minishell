/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:24:51 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/22 17:40:40 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** get_paths - split $PATH
 * @env: ms->env
 * 
 * browse the env array to find the PATH variable and splits its content.
 *
 * Returns: the splitted paths for $PATH, or an empty split if $PATH is not set
 * (NULL if malloc failed)
 */
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

/** cmd_exists - check if the command exists at this path
 * @cmd: the cmd given in input
 * @path: the path to test
 * 
 * adds the cmd after the path then checks with access if the 
 * cmd can be executed.
 * 
 * Returns: 
 * -1 if malloc failed
 * 0 if the cmd doesnt exist
 * 1 if the cmd exists
 */
int	cmd_exists(char *cmd, char *path)
{
	char	*join;
	char	*join2;

	join = ft_strjoin(path, "/");
	if (!join)
		return (perror("malloc"), -1);
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

/** add_paths - build the path string
 * @path: the path found by get_cmd_path function
 * @cmd: the cmd name given in input
 * 
 * add the path as a prefix of the cmd for execve to find it
 *
 * Returns: mallocd built string or NULL on malloc error
 */
char	*add_paths(char *path, char *cmd)
{
	char	*new;
	char	*tmp;

	if (!path && !cmd)
		return (NULL);
	if (!path)
		return (cmd);
	if (!cmd)
		return (path);
	new = ft_strjoin(path, "/");
	if (!new)
		return (perror("malloc"), NULL);
	tmp = new;
	new = ft_strjoin(tmp, cmd);
	free(tmp);
	return (new);
}

/** get_cmd_path - find the right path to execute
 * @cmd: t_token->data->cmd
 * @paths: an array of string containing the split of all the paths in $PATH
 * 
 * search for the right PATH to execute the command. If none is found, just
 * returns the cmd given in input.
 *
 * Returns:
 * -mallocd path of cmd if one is matching
 * -mallocd cmd name if none
 * -NULL on malloc error
 */
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

/** init_cmd - set the cmd token values before executing
 * @node: current tree node carrying a T_CMD type token
 * @ms: the minishell struct
 * 
 * init_cmd expand the command arguments, then checks for the 
 * right path to execute the cmd in execve.
 * if the cmd given in input has an absolute path, it keeps it.
 *
 * Returns: 1 on malloc error, 0 else
 */
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
				return (perror("malloc"), 1);
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
