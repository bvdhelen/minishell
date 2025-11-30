/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:00:00 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/30 12:51:12 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

extern int			g_exit_status;

/* ---------------------- TOKENS / COMMANDS / STRUCTS ---------------------- */

typedef enum e_tok_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		type;
	char			*value;
	char			*meta;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_wbuild
{
	char	*buf;
	size_t	len;
	size_t	cap;
	char	*mbuf;
	size_t	mlen;
	size_t	mcap;
}	t_wbuild;

typedef struct s_expand
{
	char		*out;
	size_t		len;
	size_t		cap;
	size_t		i;
	const char	*meta;
	char		**envp;
	int			last;
}	t_expand;

/* ------------------------------ CORE / MAIN ------------------------------ */

void	main_loop(char ***envp_addr);
void	error_exit(const char *msg, int code);

/* ----------------------------- ENV UTILITIES ----------------------------- */

char	**dup_envp(char **envp);
void	free_envp(char **envp);
int		valid_identifier(const char *s);
int		count_env(char **envp);
int		env_index(char **envp, const char *key);
char	**env_set(char **envp, const char *key, const char *value);
char	**env_unset(char **envp, const char *key);
char	*join_keyvalue(const char *key, const char *value);
char	**duplicate_env_and_sort(char **envp);

/* -------------------------------- BUILTINS ------------------------------- */

int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(char **envp);
int		ft_cd(char **argv, char ***envp_addr);
int		ft_export(char **argv, char ***envp_addr);
int		ft_unset(char **argv, char ***envp_addr);
int		ft_exit(char **argv);

/* --------------------------- EXEC / ROUTER / PIPE ------------------------ */

int		is_child_builtin(char *cmd);
int		is_parent_builtin(char *cmd);
int		execute_child_builtin(t_cmd *cmd, char **envp);
int		execute_parent_builtin(t_cmd *cmd, char ***envp_addr);
int		run_parent_builtin_with_redirs(t_cmd *cmd, char ***envp_addr);

void	execute_commands(t_cmd *cmds, char ***envp_addr);

int		execute_command(t_cmd *cmd, char ***envp_addr);
void	execute_command_direct(t_cmd *cmd, char **envp);
int		execute_pipeline(t_cmd *cmd_list, char ***envp_addr);

int		apply_redirs(t_cmd *cmd);
int		set_heredoc_infile(t_cmd *cmd, const char *delim);

/* -------------------------- TOKENIZER / PARSER --------------------------- */

t_token	*tokenize(const char *line);
void	free_tokens(t_token *tok);
void	print_tokens(t_token *tok);

t_cmd	*parse_pipeline(t_token *tok);
int		append_cmd(t_cmd **head, t_cmd *node);
void	free_cmds(t_cmd *cmd);

int		handle_redir_tokens(t_token **tok, t_cmd *cmd);
int		handle_pipe(const char *line, size_t *i, t_token **head);
int		handle_redir(const char *line, size_t *i, t_token **head);

/* ------------------------- TOKENIZER BUFFER UTILS ------------------------ */

char	*ft_strndup(const char *s, size_t n);
int		buf_ensure(char **buf, size_t *cap, size_t need);
int		buf_append_chars(char **buf, size_t *len, size_t *cap,
			const char *s);
int		buf_append_char(char **buf, size_t *len, size_t *cap, char c);

/* ----------------------- TOKENIZER WORD / QUOTING ------------------------ */

int		append_repeat(t_wbuild *b, char tag, size_t count);
char	*read_word(const char *line, size_t *i, int *err, char **out_meta);

char	**ft_split_with_quotes(const char *s);
char	**free_split(char **arr, int filled);

/* ------------------------------- EXPANDER -------------------------------- */

int		is_var_first(int c);
int		is_var_next(int c);
char	*lookup_env(const char *name, char **envp);
int		expand_tokens(t_token *head, char **envp, int last_status);
char	*expand_word(const char *in, const char *meta,
			char **envp, int last);

/* ---------------------------- CMD PATH / UTILS --------------------------- */

char	*get_cmd_path(char *cmd, char **envp);
void	free_paths(char **paths);

/* -------------------------------- SIGNALS -------------------------------- */

void	set_interactive_signals(void);
void	set_parent_signals(void);
void	set_child_signals(void);
void	handle_child_status(int status);

#endif
