/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:07:05 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/29 14:30:57 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_repeat(char **mbuf, size_t *mlen,
			size_t *mcap, char tag, size_t n)
{
	size_t	k;

	k = 0;
	while (k < n)
	{
		if (!buf_append_char(mbuf, mlen, mcap, tag))
			return (0);
		k++;
	}
	return (1);
}

static int	handle_single_quote(const char *line, size_t *i,
		char **buf, size_t *len, size_t *cap,
		char **mbuf, size_t *mlen, size_t *mcap, int *err)
{
	size_t	start;

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
	if (!append_repeat(mbuf, mlen, mcap, 'S', *i - start))
		return (0);
	(*i)++;
	return (1);
}

static int	handle_double_quote(const char *line, size_t *i,
		char **buf, size_t *len, size_t *cap,
		char **mbuf, size_t *mlen, size_t *mcap, int *err)
{
	size_t	start;

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
	if (!append_repeat(mbuf, mlen, mcap, 'A', *i - start))
		return (0);
	(*i)++;
	return (1);
}

static int	process_word_char(const char *line, size_t *i,
		char **buf, size_t *len, size_t *cap,
		char **mbuf, size_t *mlen, size_t *mcap, int *err)
{
	if (line[*i] == '\'')
		return (handle_single_quote(line, i, buf, len,
				cap, mbuf, mlen, mcap, err));
	if (line[*i] == '"')
		return (handle_double_quote(line, i, buf, len,
				cap, mbuf, mlen, mcap, err));
	if (!buf_append_char(buf, len, cap, line[*i]))
		return (0);
	if (!buf_append_char(mbuf, mlen, mcap, 'A'))
		return (0);
	(*i)++;
	return (1);
}

char	*read_word(const char *line, size_t *i, int *err, char **out_meta)
{
	char	*buf;
	size_t	cap;
	size_t	len;
	char	*mbuf;
	size_t	mcap;
	size_t	mlen;

	buf = NULL;
	cap = 0;
	len = 0;
	mbuf = NULL;
	mcap = 0;
	mlen = 0;
	while (line[*i] && !isspace((unsigned char)line[*i]) && line[*i] != '|')
	{
		if (!process_word_char(line, i, &buf, &len,
				&cap, &mbuf, &mlen, &mcap, err) || *err)
		{
			free(buf);
			free(mbuf);
			return (NULL);
		}
	}
	if (!buf)
	{
		buf = ft_strndup("", 0);
		mbuf = ft_strndup("", 0);
		if (!buf || !mbuf)
		{
			free(buf);
			free(mbuf);
			return (NULL);
		}
	}
	*out_meta = mbuf;
	return (buf);
}
