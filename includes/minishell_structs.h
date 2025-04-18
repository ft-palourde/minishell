/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:36 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/18 16:27:44 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H
# include <stdbool.h>

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

/* typedef struct s_token
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

struct	s_cmd
{
	char	**args;
	char	*path;
	bool	is_builtin;
}	t_cmd;

struct s_redir
{
	bool	is_append;
	bool	is_truncate;
} t_redir;

union u_data
{
	struct s_cmd	cmd;
	struct s_redir	rd;
};

/* {
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
	union u_data	data;
	struct s_token	*next;
}	t_token;

#endif