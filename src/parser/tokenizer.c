/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:06:52 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/14 11:42:50 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_word_token(t_token **head, char *w, char *m)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (free(w), free(m), 0);
	new->type = T_WORD;
	new->value = w;
	new->meta = m;
	new->next = NULL;
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

static int	handle_word_result(char *w, char *m, int err, t_token **head)
{
	if (err)
	{
		fprintf(stderr, "minishell: syntax error: unclosed quote\n");
		free(w);
		free(m);
		return (0);
	}
	if (!w || !m)
	{
		free(w);
		free(m);
		return (0);
	}
	if (!append_word_token(head, w, m))
		return (0);
	return (1);
}

static int	process_step(const char *line, size_t *i, t_token **head)
{
	int		r;
	int		err;
	char	*w;
	char	*m;

	r = handle_pipe(line, i, head);
	if (r != 0)
	{
		if (r < 0)
			return (-1);
		return (1);
	}
	err = 0;
	m = NULL;
	w = read_word(line, i, &err, &m);
	if (!handle_word_result(w, m, err, head))
		return (-1);
	return (1);
}

t_token	*tokenize(const char *line)
{
	t_token	*head;
	size_t	i;

	if (!line)
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && isspace((unsigned char)line[i]))
			i++;
		if (!line[i])
			break ;
		if (process_step(line, &i, &head) < 0)
		{
			free_tokens(head);
			return (NULL);
		}
	}
	return (head);
}
