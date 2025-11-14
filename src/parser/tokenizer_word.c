/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:07:05 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/14 13:23:16 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_builder(t_wbuild *b)
{
	b->buf = NULL;
	b->len = 0;
	b->cap = 0;
	b->mbuf = NULL;
	b->mlen = 0;
	b->mcap = 0;
}

static int	append_quoted(const char *line, size_t start,
		size_t end, t_wbuild *b)
{
	size_t	k;

	k = start;
	while (k < end)
	{
		if (!buf_append_char(&b->buf, &b->len, &b->cap, line[k]))
			return (0);
		k++;
	}
	return (1);
}

static int	handle_quote(const char *line, size_t *i, t_wbuild *b, int *err)
{
	size_t	start;
	char	q;
	char	tag;

	q = line[*i];
	tag = 'A';
	if (q == '\'')
		tag = 'S';
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != q)
		(*i)++;
	if (!line[*i])
	{
		*err = 1;
		return (0);
	}
	if (!append_quoted(line, start, *i, b))
		return (0);
	if (!append_repeat(b, tag, *i - start))
		return (0);
	(*i)++;
	return (1);
}

static int	process_word_char(const char *line, size_t *i, t_wbuild *b,
		int *err)
{
	(void)err;
	if (line[*i] == '\'' || line[*i] == '"')
		return (handle_quote(line, i, b, err));
	if (!buf_append_char(&b->buf, &b->len, &b->cap, line[*i]))
		return (0);
	if (!buf_append_char(&b->mbuf, &b->mlen, &b->mcap, 'A'))
		return (0);
	(*i)++;
	return (1);
}

char	*read_word(const char *line, size_t *i, int *err, char **out_meta)
{
	t_wbuild	b;

	init_builder(&b);
	while (line[*i] && !isspace((unsigned char)line[*i]) && line[*i] != '|')
	{
		if (!process_word_char(line, i, &b, err) || *err)
		{
			free(b.buf);
			free(b.mbuf);
			return (NULL);
		}
	}
	*out_meta = b.mbuf;
	return (b.buf);
}
