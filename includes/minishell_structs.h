/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:36 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/16 16:18:50 by tcoeffet         ###   ########.fr       */
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

typedef struct s_token
{
	t_attribute	attribute;
	t_built_in	built_in;
	char		*str;
}				t_token;

typedef struct s_input
{
	char	*line;
	int		retval;
}				t_input;

#endif