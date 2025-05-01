/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:36 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/05/01 15:02:18 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef enum e_attribute
{
	A_CMD,
	A_OPT,
	A_ARG,
	A_PIPE,
	A_OUT_A,
	A_OUT_T,
	A_IN,
	A_HD,
	A_LIM
}				t_attribute;

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
	B_NONE,
	B_CD,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_UNSET,
	B_ENV,
	B_EXIT
}			t_built_in;

typedef enum e_conf
{
	C_EMPTY,
	C_SIMPLE,
	C_PIPE,
	C_REDIRECT,
	C_HEREDOC,
	C_EXIT
}				t_conf;

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
	bool			is_builtin;
}	t_cmd;

typedef union u_rd
{
	struct s_rd_file	*file;
	struct s_rd_heredoc	*heredoc;
}	t_rd;

typedef struct s_rd_heredoc
{
	int				fd[2];
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
	struct s_tree	*left;
	struct s_tree	*right;
	t_token			*token;
}			t_tree;

#endif
