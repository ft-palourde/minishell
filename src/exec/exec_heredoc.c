#include "minishell.h"

int	add_new_hd(t_ms *ms, t_token *token)
{
	int		*pfd;
	char	*line;
	int		len;

	pfd = ft_calloc(2, sizeof(int));
	if (!pfd)
		return (0);
	if (pipe(pfd) == -1)
		return (1);
	token->data->rd->heredoc->fd = pfd;
	len = ft_strlen(token->data->rd->heredoc->lim);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, token->data->rd->heredoc->lim, len))
			break ;
		ft_putstr_fd(line, pfd[1]);
		write(pfd[1], "\n", 1);
	}
	close(pfd[1]);
	if (!add_fd(pfd[0], ms))
		return (1);
	return (0);
}

int	get_heredocs_pfd(t_ms *ms)
{
	t_token	*cursor;

	cursor = ms->token;
	while (cursor)
	{
		if (cursor->type == T_HEREDOC)
			if (add_new_hd(ms, cursor))
				return (1);
		cursor = cursor->next;
	}
	return (0);
}

int	pipe_heredoc(t_tree *node, t_ms *ms)
{
	int	*pfd;

	pfd = ft_calloc(2, sizeof(int));
	if (!pfd || pipe(pfd) == -1)
		return (1);
	node->parent->token->in_fd = pfd[0];
	node->token->out_fd = pfd[1];
	if (add_fd(pfd[0], ms) || add_fd(pfd[1], ms) || add_pfd(pfd, ms))
		return (1);
	return (0);
}

//si parent.type == T_CMD alors piper le resultat de hd dans le infile du parent

int	exec_heredoc(t_tree *node, t_ms *ms)
{
	char	*line;

	node->token->in_fd = ms->file_in;
	node->token->out_fd = ms->file_out;
	if (node->parent->token->type == T_CMD)
		if (pipe_heredoc(node, ms))
			return (1);
	dup_handler(node->token, ms);
	line = get_next_line(node->token->data->rd->heredoc->fd[0]);
	if (!line)
		return (1);
	while (line)
	{
		ft_putstr_fd(line, node->token->out_fd);
		free(line);
		line = get_next_line(node->token->data->rd->heredoc->fd[0]);
	}
	reset_dup(node->token->in_fd, node->token->out_fd, ms);
	return (0);
}

/*
trouver une solution pour bien piper le heredoc dans le parent, verifier que le duphandler ecrit bien au bon endroit
+ fix la redir j'ai un segfault.
*/