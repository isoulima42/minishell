/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:14:12 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 12:09:13 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*target;
	int				expand;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	int		status;
}	t_shell;

typedef struct s_expand
{
	char	*buf;
	t_list	*fields;
	int		started;
	int		quote;
}	t_expand;

extern int	g_signal;

/* main / loop */
int		shell_loop(t_shell *sh);
void	shell_cleanup(t_shell *sh);

/* env */
t_env	*env_init(char **envp);
t_env	*env_find(t_env *env, const char *key);
char	*env_get(t_env *env, const char *key);
int		env_set(t_env **env, const char *key, const char *value);
void	env_unset(t_env **env, const char *key);
char	**env_to_array(t_env *env);
void	env_free(t_env *env);
t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **env, t_env *node);

/* lexer */
t_token	*lexer(const char *line, int *err);
void	token_add(t_token **lst, t_token *new);
t_token	*token_new(char *value, t_token_type type);
void	token_free(t_token *tokens);
int		skip_spaces(const char *s);
int		lex_operator(t_token **tokens, const char *s);
int		lex_word(t_token **tokens, const char *s, int *err);
int		word_len(const char *s, int *unclosed);
int		is_space(char c);
int		is_operator_char(char c);

/* parser */
t_cmd	*parser(t_token *tokens, int *err);
int		parse_redir(t_cmd *cmd, t_token **tok);
int		cmd_add_arg(t_cmd *cmd, char *arg);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*cmd_new(void);
void	cmd_free(t_cmd *cmds);
int		syntax_check(t_token *tokens);

/* expand */
int		expand_cmds(t_shell *sh, t_cmd *cmds);
char	**expand_word(t_shell *sh, const char *word);
char	*expand_heredoc_line(t_shell *sh, const char *line);
char	*var_value(t_shell *sh, const char *name);

/* expand internals */
void	init_expand(t_expand *e);
int		append_str(t_expand *e, const char *s);
int		append_char(t_expand *e, char c);
int		append_split(t_expand *e, const char *s);
void	finalize_field(t_expand *e);
int		run_expand(t_shell *sh, t_expand *e, const char *word);
int		is_closing_quote(t_expand *e, char c);
int		expand_dollar(t_shell *sh, t_expand *e, const char *s);
int		read_name(const char *s);
int		append_value(t_expand *e, char *val);
char	**fields_to_array(t_list *fields);
char	**expand_abort(t_expand *e);

/* exec */
int		execute(t_shell *sh);
int		run_pipeline(t_shell *sh);
int		exec_child(t_shell *sh, t_cmd *cmd);
char	*resolve_path(t_env *env, const char *cmd);
int		apply_redirs(t_redir *redirs);
int		report_status(int wstatus);

/* heredoc */
int		collect_heredocs(t_shell *sh, t_cmd *cmds);

/* builtins */
int		is_builtin(const char *name);
int		run_builtin(t_shell *sh, t_cmd *cmd);
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_env(t_shell *sh);
int		builtin_cd(t_shell *sh, t_cmd *cmd);
int		builtin_export(t_shell *sh, t_cmd *cmd);
int		builtin_unset(t_shell *sh, t_cmd *cmd);
int		builtin_exit(t_shell *sh, t_cmd *cmd);
int		export_print(t_env *env);

/* signals */
void	set_signals_interactive(void);
void	set_signals_exec(void);
void	set_signals_child(void);
void	set_signals_heredoc(void);

/* utils */
void	print_error(const char *ctx, const char *arg, const char *msg);
void	free_array(char **arr);
int		is_valid_identifier(const char *s);
char	*ft_strjoin3(const char *a, const char *b, const char *c);
int		ft_strcmp(const char *s1, const char *s2);

#endif
