/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:31:21 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/27 11:19:48 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_byte(const char *in, t_expand *e)
{
	if (!buf_append_char(&e->out, &e->len, &e->cap, in[e->i]))
		return (0);
	e->i++;
	return (1);
}

static int	append_status(t_expand *e)
{
	char	buf[16];
	int		n;

	n = snprintf(buf, sizeof(buf), "%d", e->last);
	if (n < 0)
		return (0);
	if (!buf_append_chars(&e->out, &e->len, &e->cap, buf))
		return (0);
	e->i += 2;
	return (1);
}

static int	append_var(const char *in, t_expand *e)
{
	size_t	j;
	char	*name;
	char	*val;

	j = e->i + 1;
	if (!is_var_first((unsigned char)in[j]))
		return (append_byte(in, e));
	while (is_var_next((unsigned char)in[j]))
		j++;
	name = ft_strndup(in + e->i + 1, j - (e->i + 1));
	if (!name)
		return (0);
	val = lookup_env(name, e->envp);
	free(name);
	if (!val)
		return (0);
	if (!buf_append_chars(&e->out, &e->len, &e->cap, val))
		return (free(val), 0);
	free(val);
	e->i = j;
	return (1);
}

static int	process_chunk(const char *in, t_expand *e)
{
	if (e->meta && e->meta[e->i] == 'S')
		return (append_byte(in, e));
	if (in[e->i] == '$' && in[e->i + 1]
		&& in[e->i + 1] == '?')
		return (append_status(e));
	if (in[e->i] == '$')
		return (append_var(in, e));
	return (append_byte(in, e));
}

char	*expand_word(const char *in, const char *meta, char **envp, int last)
{
	t_expand	e;

	e.out = NULL;
	e.len = 0;
	e.cap = 0;
	e.i = 0;
	e.meta = meta;
	e.envp = envp;
	e.last = last;
	while (in[e.i])
	{
		if (!process_chunk(in, &e))
		{
			free(e.out);
			return (NULL);
		}
	}
	if (!e.out)
		e.out = ft_strndup("", 0);
	return (e.out);
}
