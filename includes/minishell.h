/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:04:19 by eldiaz-c          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/23 12:17:44 by joperez2         ###   ########.fr       */
=======
/*   Updated: 2025/10/23 14:15:41 by eldiaz-c         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <sys/stat.h> //para q??

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
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char            **argv;
	struct s_cmd    *next;
}   t_cmd;

/* tokenizer / parser public API */
t_token	*tokenize(const char *line);
void	free_tokens(t_token *tok);
void	print_tokens(t_token *tok);
char	**free_split(char **arr, int filled);

/* helpers used across tokenizer files */
char	*ft_strndup(const char *s, size_t n);
int		buf_ensure(char **buf, size_t *cap, size_t need);
int		buf_append_chars(char **buf, size_t *len, size_t *cap, const char *s, size_t n);
int		buf_append_char(char **buf, size_t *len, size_t *cap, char c);

/* functions implemented in tokenizer_word.c used by tokenizer.c */
char	*read_word(const char *line, size_t *i, int *err);

/* pipe handler (separated) */
int		handle_pipe(const char *line, size_t *i, t_token **head);

/* quotes split */
char	**ft_split_with_quotes(const char *s);

<<<<<<< HEAD
/* PARSER */
t_cmd   *parse_pipeline(t_token *tok);
void    free_cmds(t_cmd *cmd);

/* helpers parser */
int     append_cmd(t_cmd **head, t_cmd *node);
int     push_arg(t_cmd *cmd, const char *word);

/* EXPANDER */
int     expand_tokens(t_token *head, char **envp, int last_status);
int     is_var_first(int c);
int     is_var_next(int c);
char    *lookup_env(const char *name, char **envp);
char    *expand_word(const char *in, char **envp, int last_status);
=======
/* ================================================
**					EXECUTION
** ================================================ */

typedef struct s_cmd
{
	char 			**argv;
	int				infile;
	int				outfile;
	int				is_builtin;
	struct s_cmd	*next;
}	t_cmd;

/* builtins */
int		ft_echo(char **argv);
int		ft_cd(char **argv);
int		ft_pwd(char **argv);
int		ft_export(char **argv, char **envp);
int		ft_unset(char **argv, char **envp);
int		ft_env(char **envp);
int		ft_exit(char **argv);

/* execution */
int		execute_command(t_cmd *cmd, char **envp);
int		execute_pipeline(t_cmd *cmd_list, char **envp);

/* signals */
void	setup_signals(void);

/* error */
void	error_exit(const char *msg, int code);
>>>>>>> refs/remotes/origin/main

#endif