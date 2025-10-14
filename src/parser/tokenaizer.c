#include "./minishell.h"

static char *ft_strndup(const char *s, size_t n)
{
    char *r;
    
    r = malloc(n + 1);
    if (!r)
        return NULL;
    memcpy(r, s, n);
    r[n] = '\0';
    return (r);
}

static t_token *new_token(t_tok_type type, char *value)
{
    t_token *t;
    
    t = malloc(sizeof(t_token));
    if (!t)
    {
        free(value);
        return NULL;
    }
    t->type = type;
    t->value = value;
    t->next = NULL;
    return (t);
}

static int append_token(t_token **head, t_token *new)
{
    t_token *tmp;

    if (!new)
        return 0;
    if (!*head)
    {
        *head = new;
        return (1);
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (1);
}

static int buf_ensure(char **buf, size_t *cap, size_t need)
{
    if (*cap >= need)
        return (1);
    size_t nc;

    if (*cap)
        nc = *cap * 2;
    else
        nc = 64;
    while (nc < need)
        nc *= 2;
    char *nb = realloc(*buf, nc);
    if (!nb)
        return (0);
    *buf = nb;
    *cap = nc;
    return (1);
}

static int buf_append_chars(char **buf, size_t *len, size_t *cap, const char *s, size_t n)
{
    if (!buf_ensure(buf, cap, *len + n + 1))
        return (0);
    if (n)
        memcpy(*buf + *len, s, n);
    *len += n;
    (*buf)[*len] = '\0';
    return (1);
}

static int buf_append_char(char **buf, size_t *len, size_t *cap, char c)
{
    return (buf_append_chars(buf, len, cap, &c, 1));
}

static int handle_single_quote(const char *line, size_t *i,
        char **buf, size_t *len, size_t *cap, int *err)
{
    size_t start;

    (*i)++;
    start = *i;
    while (line[*i] && line[*i] != '\'')
        (*i)++;
    if (!line[*i])
        return (*err = 1, 0);
    if (!buf_append_chars(buf, len, cap, line + start, *i - start))
        return 0;
    (*i)++;
    return (1);
}

static int handle_double_quote(const char *line, size_t *i,
        char **buf, size_t *len, size_t *cap, int *err)
{
    size_t start;

    (*i)++;
    start = *i;
    while (line[*i] && line[*i] != '"')
        (*i)++;
    if (!line[*i])
        return (*err = 1, 0);
    if (!buf_append_chars(buf, len, cap, line + start, *i - start))
        return 0;
    (*i)++;
    return (1);
}

static int process_word_char(const char *line, size_t *i,
    char **buf, size_t *len, size_t *cap, int *err)
{
    if (line[*i] == '\'')
    {
        if (!handle_single_quote(line, i, buf, len, cap, err))
            return (0);
    }
    else if (line[*i] == '"')
    {
        if (!handle_double_quote(line, i, buf, len, cap, err))
            return (0);
    }
    else
    {
        if (!buf_append_char(buf, len, cap, line[*i]))
            return (0);
        (*i)++;
    }
    return (1);
}

static char *read_word(const char *line, size_t *i, int *err)
{
    char *buf;
    size_t cap;
    size_t len;

    buf = NULL;
    cap = 0;
    len = 0;
    while (line[*i] && !isspace((unsigned char)line[*i]) && line[*i] != '|')
    {
        if (!process_word_char(line, i, &buf, &len, &cap, err))
        {
            free(buf);
            return (NULL);
        }
        if (*err)
        {
            free(buf);
            return (NULL);
        }
    }
    if (!buf)
    {
        buf = malloc(1);
        if (!buf)
            return (NULL);
        buf[0] = '\0';
    }
    return (buf);
}

static int handle_pipe(const char *line, size_t *i, t_token **head)
{
    char *v;

    if (line[*i] != '|')
        return 0;
    v = ft_strndup("|", 1);
    if (!v)
        return -1;
    if (!append_token(head, new_token(T_PIPE, v)))
    {
        free(v);
        return (-1);
    }
    (*i)++;
    return (1);
}

static int handle_word_result(char *w, int err, t_token **head)
{
    if (err)
    {
        fprintf(stderr, "minishell: syntax error: unclosed quote\n");
        free(w);
        free_tokens(*head);
        return (0);
    }
    if (w == NULL)
    {
        free_tokens(*head);
        return (0);
    }
    if (!append_token(head, new_token(T_WORD, w)))
    {
        free(w);
        free_tokens(*head);
        return (0);
    }
    return (1);
}

t_token *tokenize(const char *line)
{
    t_token *head;
    size_t i;
    char *w;
    int err;

    i = 0;
    while (line[i])
    {
        while (line[i] && isspace((unsigned char)line[i]))
            i++;
        if (!line[i])
            break;
        if (handle_pipe(line, &i, &head) == -1)
        {
            free_tokens(head);
            return (NULL);
        }
        if (!line[i])
            break;
        err = 0;
        w = read_word(line, &i, &err);
        if (!handle_word_result(w, err, &head))
            return (NULL);
    }
    return (head);
}


void free_tokens(t_token *tok)
{
    t_token *tmp;

    while (tok)
    {
        tmp = tok->next;
        if (tok->value)
            free(tok->value);
        free(tok);
        tok = tmp;
    }
}

void print_tokens(t_token *tok)
{
    const char *name;

    while (tok)
    {
        if (tok->type == T_WORD)
            name = "WORD";
        else if (tok->type == T_PIPE)
            name = "PIPE";
        else
            name = "OTHER";

        if (tok->value)
            printf("[%s] '%s'\n", name, tok->value);
        else
            printf("[%s] '(null)'\n", name);

        tok = tok->next;
    }
}

