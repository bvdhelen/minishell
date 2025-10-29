/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:08:26 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/29 14:27:46 by eldiaz-c         ###   ########.fr       */
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
	nc = *cap ? *cap * 2 : 64;
	while (nc < need)
		nc *= 2;
	nb = realloc(*buf, nc);
	if (!nb)
		return (0);
	*buf = nb;
	*cap = nc;
	return (1);
}

int	buf_append_chars(char **buf, size_t *len, size_t *cap,
				const char *s, size_t n)
{
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
	return (buf_append_chars(buf, len, cap, &c, 1));
}
