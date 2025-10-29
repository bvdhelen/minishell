/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:31:21 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/29 14:32:06 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_status(char **out, size_t *len,
			size_t *cap, size_t *i, int last)
{
	char	buf[16];
	int		n;

	n = snprintf(buf, sizeof(buf), "%d", last);
	if (n < 0)
		return (0);
	if (!buf_append_chars(out, len, cap, buf, (size_t)n))
		return (0);
	*i += 2;
	return (1);
}

static int	append_var(const char *in, char **out, size_t *len, size_t *cap,
				size_t *i, char **envp)
{
	size_t	j;
	char	*name;
	char	*val;

	j = *i + 1;
	if (!is_var_first((unsigned char)in[j]))
		return (buf_append_chars(out, len, cap, in + (*i)++, 1));
	while (is_var_next((unsigned char)in[j]))
		j++;
	name = ft_strndup(in + *i + 1, j - (*i + 1));
	if (!name)
		return (0);
	val = lookup_env(name, envp);
	free(name);
	if (!val || !buf_append_chars(out, len, cap, val, strlen(val)))
		return (free(val), 0);
	free(val);
	*i = j;
	return (1);
}

static int	append_byte(const char *in, char **out, size_t *len,
				size_t *cap, size_t *i)
{
	if (!buf_append_chars(out, len, cap, in + *i, 1))
		return (0);
	(*i)++;
	return (1);
}

static int	process_chunk(const char *in, const char *meta, char **out,
		size_t *len, size_t *cap, size_t *i, char **envp, int last)
{
	if (meta && meta[*i] == 'S')
		return (buf_append_chars(out, len, cap, in + (*i)++, 1));
	if (in[*i] == '$' && in[*i + 1] == '?')
		return (append_status(out, len, cap, i, last));
	if (in[*i] == '$')
		return (append_var(in, out, len, cap, i, envp));
	return (append_byte(in, out, len, cap, i));
}

char	*expand_word(const char *in, const char *meta, char **envp, int last)
{
	char	*out;
	size_t	len;
	size_t	cap;
	size_t	i;

	out = NULL;
	len = 0;
	cap = 0;
	i = 0;
	while (in[i])
	{
		if (!process_chunk(in, meta, &out, &len, &cap, &i, envp, last))
			return (free(out), NULL);
	}
	if (!out)
		out = ft_strndup("", 0);
	return (out);
}
