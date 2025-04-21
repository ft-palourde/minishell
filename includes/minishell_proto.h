/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/18 17:55:13 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTO_H
# define MINISHELL_PROTO_H

char			*get_prompt(char **env);

/*  */

/*  */

/* LEXER */
/* takes readline output as argument and returns a list of tokens*/
t_token			*lexer(char *input);
// t_token			*lexer(void);

/* LEXER UTILS */
/* c == white space ? 1 : 0*/
int				is_space(char c);

/* TOKEN */

/* token constructor */
t_token			*constr_new_token(t_token_type type, char *str);
void			add_to_tokens(t_token *new_token, t_token **tokens);

/* OPERATOR */
int				handle_operator(char *input, t_token **tokens);
t_token_type	get_operator_type(char *input);
int				operator_len(t_token_type type);
bool			is_operator(char c);

#endif