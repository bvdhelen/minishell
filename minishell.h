
#ifndef MINISHELL_H
#define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>

typedef enum e_tok_type
{
    T_WORD,
    T_PIPE,
    T_REDIR_IN,
    T_REDIR_OUT,
    T_REDIR_APPEND,
    T_HEREDOC
}   t_tok_type;

typedef struct s_token
{
    t_tok_type       type;
    char            *value;
    struct s_token  *next;
}   t_token;

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

/* quotes split (si la usas desde otros módulos) */
char	**ft_split_with_quotes(const char *s);

#endif