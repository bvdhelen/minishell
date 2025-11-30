/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:06:52 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/30 12:07:10 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_redir_token(t_token **head, t_tok_type type, char *v)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = type;
	new->value = v;
	new->meta = NULL;
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

static int	handle_less(const char *line, size_t *i, t_token **head)
{
	char		*v;
	t_tok_type	type;

	if (line[*i + 1] == '<')
	{
		v = ft_strndup("<<", 2);
		type = T_HEREDOC;
		*i += 2;
	}
	else
	{
		v = ft_strndup("<", 1);
		type = T_REDIR_IN;
		(*i)++;
	}
	if (!v)
		return (-1);
	if (!append_redir_token(head, type, v))
		return (free(v), -1);
	return (1);
}

static int	handle_greater(const char *line, size_t *i, t_token **head)
{
	char		*v;
	t_tok_type	type;

	if (line[*i + 1] == '>')
	{
		v = ft_strndup(">>", 2);
		type = T_REDIR_APPEND;
		*i += 2;
	}
	else
	{
		v = ft_strndup(">", 1);
		type = T_REDIR_OUT;
		(*i)++;
	}
	if (!v)
		return (-1);
	if (!append_redir_token(head, type, v))
		return (free(v), -1);
	return (1);
}

int	handle_redir(const char *line, size_t *i, t_token **head)
{
	if (line[*i] == '<')
		return (handle_less(line, i, head));
	if (line[*i] == '>')
		return (handle_greater(line, i, head));
	return (0);
}
