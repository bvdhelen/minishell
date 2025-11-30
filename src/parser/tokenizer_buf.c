/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:08:26 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/30 12:45:56 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*r;

	r = malloc(n + 1);
	if (!r)
		return (NULL);
	memcpy(r, s, n);
	r[n] = '\0';
	return (r);
}

int	buf_ensure(char **buf, size_t *cap, size_t need)
{
	size_t	nc;
	char	*nb;

	if (*cap >= need)
		return (1);
	if (*cap != 0)
		nc = (*cap) * 2;
	else
		nc = 64;
	while (nc < need)
		nc *= 2;
	nb = realloc(*buf, nc);
	if (!nb)
		return (0);
	*buf = nb;
	*cap = nc;
	return (1);
}

int	buf_append_chars(char **buf, size_t *len, size_t *cap, const char *s)
{
	size_t	n;

	n = strlen(s);
	if (!buf_ensure(buf, cap, *len + n + 1))
		return (0);
	if (n)
		memcpy(*buf + *len, s, n);
	*len += n;
	(*buf)[*len] = '\0';
	return (1);
}

int	buf_append_char(char **buf, size_t *len, size_t *cap, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (buf_append_chars(buf, len, cap, tmp));
}
