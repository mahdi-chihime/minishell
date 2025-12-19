/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:44:09 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 15:18:27 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_node_type
{
	N_CMD,
	N_PIPE,
	N_REDIR_IN,
	N_REDIR_OUT,
	N_REDIR_APPEND,
	N_HEREDOC,
	N_SUBSHELL,
	N_AND,
	N_OR
}								t_node_type;

typedef struct s_node
{
	char						**cmd;
	t_node_type					type;
	char						*file;
	int							hd_expand;
	int							hd_tmp;
	struct s_node				*left;
	struct s_node				*right;
}								t_node;

typedef struct s_env
{
	char						*key;
	char						*val;
	struct s_env				*next;
}								t_env;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR,
	T_LPAREN,
	T_RPAREN
}								t_token_type;

typedef struct s_token
{
	t_token_type				type;
	char						*value;
	int							quoted;
	struct s_token				*next;
}								t_token;

typedef struct s_expand
{
	char						*s;
	int							*i;
	t_env						*env;
	int							last;
	char						**res;
	int							*start;
}								t_expand;

typedef struct s_lexer_ctx
{
	t_env						*env;
	int							last_status;
}								t_lexer_ctx;

typedef struct s_here
{
	int							fd;
	t_node						*node;
	t_env						*env;
	int							last_status;
	char						template[24];
}								t_here;

typedef struct s_pipe_ctx
{
	t_node						*node;
	t_env						**env;
	int							last_status;
	int							fd[2];
	pid_t						pids[2];
}								t_pipe_ctx;

extern volatile sig_atomic_t	g_sig;
int								exec_tree(t_node *root, t_env **env,
									int last_status);
int								exec_cmd(t_node *node, t_env **env,
									int last_status);
int								exec_subshell(t_node *node, t_env **env,
									int last_status);
int								exec_pipe(t_node *node, t_env **env,
									int last_status);
int								handle_redirections(t_node *node, t_env *env,
									int last_status);
int								prepare_heredocs(t_node *node, t_env *env,
									int last_status);
int								do_heredoc(t_node *node, t_env *env,
									int prepare_only, int last_status);
char							**expand_wildcards(char **args);
void							heredoc_sigint(int sig);
int								read_loop(t_here *ctx);
int								close_result(t_here *ctx, int status,
									int keep_file, t_node *node);
int								is_builtin(char *s);
int								exec_builtin_node(t_node *node, t_env **env);
int								exec_run_builtin(t_node *node, t_env **env,
									t_node *cmd, int last_status);
int								fill_env_array(t_env *env, t_env ***arr,
									int *len);
void							sort_env_array(t_env **arr, int len);
int								print_export_sorted(t_env *env);
t_node							*exec_get_cmd_node(t_node *node);
int								exec_save_std(int backup[2]);
void							exec_restore_std(int backup[2]);
int								exec_apply_redirs_only(t_node *node, t_env *env,
									int last_status);
char							**prepare_args(t_node *cmd);
int								resolve_cmd_path(char *cmd, t_env *env,
									char ***envp, char **path);
int								bi_echo(char **args);
int								bi_pwd(t_env *env);
int								bi_exit(char **args);
int								bi_cd(char **args, t_env **env);
int								bi_env(t_env *env);
int								bi_export(char **args, t_env **env);
int								bi_unset(char **args, t_env **env);
t_env							*env_from_environ(char **envp);
char							*env_get(t_env *env, const char *key);
int								env_set(t_env **env, const char *key,
									const char *val, int overwrite);
int								env_unset(t_env **env, const char *key);
char							**env_to_environ(t_env *env);
char							*get_home_dir(t_env *env);
void							env_free(t_env *env);
void							free_tree(t_node *node);
void							free_split(char **split);
void							print_error(char *msg);
void							exit_error(char *msg, int code);
char							*expand_token_value(char *s, t_env *env,
									int last);
char							*expand_word(char *s, int *i, t_env *env,
									int last);
t_token							*lexer(char *input, t_env *env,
									int last_status);
t_token							*token_new(t_token_type type, char *value,
									int quoted);
char							*join_path_fallback(char *pwd, char *path);
void							init_oldpwd(char oldpwd[4096], t_env *env);
void							add_token(t_token **list, t_token_type type,
									char *val, int quoted);
t_token_type					get_op_type(char *s, int *i);
void							token_add_back(t_token **lst, t_token *new);
void							token_free(t_token *lst);
int								is_operator_char(char c);
t_node							*parse_input(char *line, t_env *env,
									int last_status);

t_node							*parse_and_or(t_token **tokens);
t_node							*parse_pipeline(t_token **tokens);
t_node							*parse_command(t_token **tokens);
t_node							*parse_factor(t_token **tokens);
t_node							*parse_subshell(t_token **tokens);
char							**collect_args(t_token **tok);
t_node							*new_pipe_node(t_node *left, t_token **tok);
t_node							*new_logic_node(t_node *left, t_node_type type,
									t_token **tok);
char							*expand_single_quote(char *s, int *i);
char							*expand_double_quotes(char *s, int *i,
									t_env *env, int last);
char							*expand_var(char *s, int *i, t_env *env,
									int last);
char							*ft_strjoin_free(char *s1, char *s2);
int								is_op(char c);
t_node							*parse_redirs(t_token **tok, t_node *cmd);
int								is_redir_token(t_token_type t);
t_node							*new_node(t_node_type type, char **cmd);
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strjoin_three(char *s1, char *s2, char *s3);
int								is_valid_key(char *s);
void							sigint_handler(int sig);
void							set_shell_signals(void);
void							set_ignore_signals(void);
int								wait_status_to_exit(int status);
char							*find_in_path(char *cmd, t_env *env);
char							*expand_line_value(char *s, t_env *env,
									int last);
char							*read_full_line(void);
char							*expand_double_quotes(char *s, int *i,
									t_env *env, int last);
void							handle_dollar_in_dquote(t_expand *ex);
int								init_heredoc_ctx(t_here *ctx, t_node *node,
									t_env *env, int last_status);
void							child_proc(t_node *left, t_env **env, int *fd,
									int last_status);
int								create_hd_file(char *out);
int								set_keep_file(t_here *ctx, t_node *node);
void							process_segment(t_expand *ex);
int								export_one(char *arg, t_env **env);
void							handle_word(char *s, int *i, t_token **list,
									t_lexer_ctx ctx);
int								is_signal_status(int status);
int								append_args(char ***dst, char **extra);
#endif
