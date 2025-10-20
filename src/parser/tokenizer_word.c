#include "../../minishell.h"

int	handle_single_quote(const char *line, size_t *i,
		char **buf, size_t *len, size_t *cap, int *err)
{
	size_t start;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (!line[*i])
	{
		*err = 1;
		return (0);
	}
	if (!buf_append_chars(buf, len, cap, line + start, *i - start))
		return (0);
	(*i)++;
	return (1);
}

int	handle_double_quote(const char *line, size_t *i,
		char **buf, size_t *len, size_t *cap, int *err)
{
	size_t start;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (!line[*i])
	{
		*err = 1;
		return (0);
	}
	if (!buf_append_chars(buf, len, cap, line + start, *i - start))
		return (0);
	(*i)++;
	return (1);
}

int	process_regular_char(const char *line, size_t *i,
		char **buf, size_t *len, size_t *cap)
{
	if (!buf_append_char(buf, len, cap, line[*i]))
		return (0);
	(*i)++;
	return (1);
}

int	process_word_char(const char *line, size_t *i,
		char **buf, size_t *len, size_t *cap, int *err)
{
	if (line[*i] == '\'')
		return (handle_single_quote(line, i, buf, len, cap, err));
	if (line[*i] == '"')
		return (handle_double_quote(line, i, buf, len, cap, err));
	return (process_regular_char(line, i, buf, len, cap));
}

char	*read_word(const char *line, size_t *i, int *err)
{
	char	*buf;
	size_t	cap;
	size_t	len;

	buf = NULL;
	cap = 0;
	len = 0;
	while (line[*i] && !isspace((unsigned char)line[*i]) && line[*i] != '|')
	{
		if (!process_word_char(line, i, &buf, &len, &cap, err) || *err)
		{
			if (buf)
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


