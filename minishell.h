
#ifndef MINISHELL_H
#define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>

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

t_token *tokenize(const char *line);
void free_tokens(t_token *tok);
void print_tokens(t_token *tok);


#endif
