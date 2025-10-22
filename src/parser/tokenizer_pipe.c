/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:06:43 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/22 15:15:21 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_pipe_token(t_token **head, char *v)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = T_PIPE;
	new->value = v;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

int	handle_pipe(const char *line, size_t *i, t_token **head)
{
	char	*v;

	if (line[*i] != '|')
		return (0);
	v = ft_strndup("|", 1);
	if (!v)
		return (-1);
	if (!append_pipe_token(head, v))
	{
		free(v);
		return (-1);
	}
	(*i)++;
	return (1);
}
