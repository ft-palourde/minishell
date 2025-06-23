/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:36 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/06/18 14:47:05 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H


/* 
{
	B_NONE,
	B_CD,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
}			t_built_in;
*/
typedef enum e_built_in
{
	B_NONE = 0,
	B_CD,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
}			t_built_in;

/*
{
	t_attribute	attribute;
	t_built_in	built_in;
	char		*value;
	t_token		*next;
}				t_token; */

typedef struct s_input
{
	char	*line;
	int		retval;
}				t_input;

/* ------------------------------------ */
/* 
{
	T_WORD,
	T_PIPE,
	T_AND_IF,
	T_OR_IF,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_UNKNOWN
}	t_token_type;
*/
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_AND_IF,
	T_OR_IF,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_CMD,
	T_UNKNOWN
}	t_token_type;
/* 
{
	char	**args;
	char	*path;
	bool	is_builtin;
}	t_cmd;
*/
typedef struct s_cmd
{
	char			**args;
	char			*path;
	t_built_in		is_builtin;
}	t_cmd;

typedef union u_rd
{
	struct s_rd_file	*file;
	struct s_rd_heredoc	*heredoc;
}	t_rd;

typedef struct s_rd_heredoc
{
	int				*fd;
	char			*lim;
}	t_rd_heredoc;

typedef struct s_rd_file
{
	int		fd;
	char	*filename;
}	t_rd_file;

/* 
{
	struct s_cmd	cmd;
	struct s_redir	rd;
};
*/
typedef union u_data
{
	struct s_cmd	*cmd;
	union u_rd		*rd;
}	t_data;

/*
{
	t_token_type	type;
	char			*str;
	union u_data	data;
	struct s_token	*next;
}	t_token;
 */
typedef struct s_token
{
	t_token_type	type;
	char			*str;
	union u_data	*data;
	struct s_token	*next;
	int				in_fd;
	int				out_fd;
}	t_token;
/* 
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_token			*token;
}	t_tree;
*/
typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
	t_token			*token;
}	t_tree;

typedef struct termios	t_termios;

/* 
typedef struct s_ms
{
	t_token	token;
	t_tree	tree;
	char	**env;
	int		file_in;
	int		file_out;
}	t_ms;
*/
typedef struct s_ms
{
	t_token		*token;
	t_termios	*term;
	t_tree		*tree;
	char		*prompt;
	char		**env;
	int			*pid;
	int			**pfd;
	int			*fd;
	int			open_failed;
	int			file_in;
	int			file_out;
	int			retval;
	int			exit;
	int			ms_stdin;
	int			ms_stdout;
}	t_ms;

#endif
