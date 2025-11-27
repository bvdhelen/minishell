/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:04:19 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/27 20:18:03 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

extern int	g_exit_status;

/* ---------------- TOKENIZER / PARSER TYPES ---------------- */

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

typedef struct s_wbuild
{
	char	*buf;
	size_t	len;
	size_t	cap;
	char	*mbuf;
	size_t	mlen;
	size_t	mcap;
}	t_wbuild;

/* ---------------- TOKENIZER / PARSER API ---------------- */

t_token	*tokenize(const char *line);
void	free_tokens(t_token *tok);
void	print_tokens(t_token *tok);
char	**free_split(char **arr, int filled);
int		append_repeat(t_wbuild *b, char tag, size_t count);

/* tokenizer buffer helpers */
char	*ft_strndup(const char *s, size_t n);
int		buf_ensure(char **buf, size_t *cap, size_t need);
int		buf_append_chars(char **buf, size_t *len, size_t *cap, const char *s);
int		buf_append_char(char **buf, size_t *len, size_t *cap, char c);

/* tokenizer_word.c */
char	*read_word(const char *line, size_t *i, int *err, char **out_meta);

/* pipe handler */
int		handle_pipe(const char *line, size_t *i, t_token **head);

/* quotes split */
char	**ft_split_with_quotes(const char *s);

/* PARSER */
t_cmd	*parse_pipeline(t_token *tok);
void	free_cmds(t_cmd *cmd);
int		append_cmd(t_cmd **head, t_cmd *node);
int		push_arg(t_cmd *cmd, const char *word);

/* parser_debug.c */
void	print_cmds(t_cmd *cmd);

/* ---------------- EXPANDER ---------------- */

int		expand_tokens(t_token *head, char **envp, int last_status);
int		is_var_first(int c);
int		is_var_next(int c);
char	*lookup_env(const char *name, char **envp);
char	*expand_word(const char *in, const char *meta,
			char **envp, int last_status);

/* ---------------- EXECUTION ---------------- */

/* error_exit.c */
void	error_exit(const char *msg, int code);

/* exec_cmd.c */
int		is_absolute_path(const char *cmd);
char	*check_direct_path(const char *cmd);
void	check_access(char *path);
void	execute_command_direct(t_cmd *cmd, char **envp);
int		execute_command(t_cmd *cmd, char ***envp_addr);

/* exec_cmd_utils.c */
char	*join_paths(const char *folder, const char *cmd);
char	*search_in_paths(char **paths, char *cmd);
char	*get_cmd_path(char *cmd, char **envp);
char	**free_memory(char **result, int count);
void	free_paths(char **paths);

/* exec_pipe.c */
int		handle_middle_cmd(t_cmd *cmd, int input_fd, char **envp);
pid_t	handle_last_cmd(t_cmd *cmd, int input_fd, char **envp);
void	wait_all(pid_t last_pid);
int		execute_pipeline(t_cmd *cmd_list, char ***envp_addr);

/* exec_builtin.c */
int		is_child_builtin(char *cmd);
int		is_parent_builtin(char *cmd);
int		execute_child_builtin(t_cmd *cmd, char **envp);
int		execute_parent_builtin(t_cmd *cmd, char ***envp_addr);

/* child_builtins.c */
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(char **envp);

/* ft_cd.c */
int		ft_cd(char **argv, char ***envp_addr);

/* ft_exit.c */
int		ft_exit(char **argv);

/* env_utils.c */
char	**dup_envp(char **envp);
void	free_envp(char **envp);
int		env_index(char **envp, const char *key);
char	*join_keyvalue(const char *key, const char *value);
char	**env_set(char **envp, const char *key, const char *value);
char	**env_unset(char **envp, const char *key);
int		valid_identifier(const char *s);

/* ft_export_unset.c */
int		count_env(char **envp);
int		key_len(const char *s);
int		compare_export_keys(char *a, char *b);
void	sort_env_export(char **arr);
char	**duplicate_env_and_sort(char **envp);
int		print_export(char **envp);
int		process_assignment(char *arg, char ***envp_addr);

int		ft_export(char **argv, char ***envp_addr);
int		ft_unset(char **argv, char ***envp_addr);

/* ---------------- SIGNALS ---------------- */

void	set_interactive_signals(void);
void	set_parent_exec_signals(void);
void	set_child_signals(void);
void	handle_child_status(int status);

/* ---------------- MAIN / LOOP ---------------- */

char	**init_env(char **envp);
int		execute_commands(t_cmd *cmds, char ***envp_addr);
int		handle_line(char *line, char ***envp_addr);
void	set_interactive_signals(void);

#endif
