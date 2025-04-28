/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoeffet <tcoeffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/04/28 11:32:32 by tcoeffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTO_H
# define MINISHELL_PROTO_H

char	*get_prompt(char **env);

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