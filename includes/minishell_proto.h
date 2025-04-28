/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/28 11:32:32 by tcoeffet         ###   ########.fr       */
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

/* QUOTES */
int				is_quote(char c);
int				handle_quote(char *input, t_token **tokens);

///////// BUILT-INS /////////

int		bi_cd(char **env, char *path);
void	bi_echo(char **arg);
int		bi_env(char **env);
int		bi_pwd(void);
int		bi_unset(char **env, char **var);
int		bi_exit(char **env);
int		bi_export(char ***args, char **env);

char	*ft_get_pwd(int prefix);

char	*get_var_value(char *var);

int		split_len(char **split);

//////// SET_ENV /////////

char	**set_env(char **env, int has_env);


#endif