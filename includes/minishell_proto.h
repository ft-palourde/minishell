/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_proto.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:44:38 by tcoeffet          #+#    #+#             */
/*   Updated: 2025/07/08 14:08:46 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTO_H
# define MINISHELL_PROTO_H

extern int	g_sig;

char			*get_prompt(char **env);

/* LEXER */

t_token			*lexer(char *input);

/* LEXER UTILS */

/* c == white space ? 1 : 0*/
int				is_space(char c);
int				extract_word_len(const char *input);

/* TOKEN */

/* token constructor */

t_token			*constr_new_token(t_token_type type, char *str);
void			add_to_tokens(t_token *new_token, t_token **tokens);
void			free_token(t_token *token);

/* OPERATOR */
int				handle_operator(char *input, t_token **tokens);
t_token_type	get_operator_type(char *input);
int				operator_len(t_token_type type);
bool			is_operator(char c);

/* QUOTES */

int				is_quote(char c);
int				handle_quote(char *input, t_token **tokens);
void			free_tokens(t_token *tokens);
int				is_backslash(char c);
int				is_escaped(char *input, int index);
void			free_cmd(t_cmd *cmd);
void			free_redir(t_rd *rd);
int				unclosed_quote(t_token *token);
int				check_quote_error(char *str, char c);

/* WORD */

t_cmd			*new_cmd(void);

/* DEBUG DISPLAY */

void			display_tokens(t_token *tokens);
void			print_token_list(t_token *token);
void			debug_display_token_args(t_token *tokens);

/* PARSE */
t_token			*parse(char *input);
void			parse_cmd(t_token *token);

/* PARSE UTILS */
void			parse_rd_file(t_token *token);
void			parse_heredoc(t_token *token);
int				is_word(t_token *token);
int				is_closed(char *str, char c);

/* EXPAND */

char			*hd_expand(t_ms *ms, char *str);
char			*get_next_chunk(char *str);
char			*expand_chunk(char *str, t_ms *ms);
char			*str_expand(char *str, t_ms *ms);
char			*get_next_chunk(char *str);
int				check_quote_type(char c);
void			add_var_to_new(char **new, char *str, int *i, t_ms *ms);
int				expand_is_closed(char *str, char c);
char			*var_name_to_value(char *name, t_ms *ms);
char			*var_expand(char *str, int *j, t_ms *ms);
void			expand_cmd_args(t_cmd **cmd, t_ms *ms);
char			*expand_path(char *str, t_ms *ms);
char			*ft_get_pid(void);

/* SIGNAL */

void			ms_signal_listener(void);
void			handle_sigint(int sig);
int				sig_comp(int sig);
void			handle_sigint_hd(int sig);
void			sig_ignore(void);
void			reset_dlt_sig_behavior(void);
void			set_hd_sig_behavior(void);

///////// BUILT-INS /////////

int				bi_cd(char **env, char *path);
int				bi_echo(char **arg);
int				bi_env(char **env);
int				bi_pwd(void);
int				bi_unset(char **env, char **var);
int				bi_exit(t_ms *ms, char **arg);
int				bi_export(char ***env, char **args);

char			*ft_get_pwd(int prefix);

int				unset(char **env, char *var);

char			*get_var_value(char *var);
char			*get_var_name(char *var);
int				var_exists(char **env, char *var);
int				var_is_empty(char *var);
int				is_var(char *var);

int				split_len(char **split);

int				is_builtin(t_token *token);

//////// SET_ENV /////////

char			**set_env(char **env);

//////// TREE BUILD /////////

int				check_outfile(t_token *list, t_tree *node);
void			new_branch(int is_left, t_tree *parent, t_tree *child);
int				fill_tree(t_tree *node, t_token *list);
int				build_tree(t_ms *ms);
t_tree			*get_root(t_tree *node);
t_tree			*get_new_node(t_token *token);
void			debug_print_tree(t_tree *root, int i);

//////// SORT TOKENS /////////

void			sort_tokens(t_ms *ms);

//////// EXEC /////////

int				init_cmd(t_tree *node, t_ms *ms);
void			reset_ms_files(t_ms *ms);

int				add_pid(int pid, t_ms *ms);

void			exec_cmd(t_tree *node, t_ms *ms);
int				exec_tree(t_tree *root, t_ms *ms);
int				exec_init(t_ms *ms);
int				exec_pipe(t_tree *node, t_ms *ms);
int				exec_redir(t_token *token, t_ms *ms);
int				get_heredocs_pfd(t_ms *ms);
void			fill_new_hd(t_ms *ms, int *fd, char *lim, int expand);
int				check_lim(char	*lim);
unsigned char	wait_child(pid_t cpid);
void			abort_heredoc(t_ms *ms, int *fd);

void			reset_dup(int in_fd, int out_fd, t_ms *ms);
void			dup_handler(t_token *token, t_ms *ms);
void			reset_std_dup(t_ms *ms);

int				is_absolute(char *str);
int				is_redir(t_token_type type);

int				add_fd(int fd, t_ms *ms);
int				add_pfd(int *pfd, t_ms *ms);
void			close_fds(t_ms *ms);
void			clear_all(t_ms *ms);
void			clean_fds(int *fd);
void			clean_pfds(int	**pfd);
//////// CLEANER /////////

void			free_split(char **split);
void			free_tree(t_tree *tree);
void			ms_cleaner(t_ms *ms);
void			ms_full_clean(t_ms *ms);

////// COMMON_UTILS //////

void			display_nl(int sig);

/* INIT */

t_ms			*init_ms_struct(char **env);

#endif