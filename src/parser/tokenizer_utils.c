/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:10:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/26 13:10:49 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*safe_val(char *v)
{
	if (v)
		return (v);
	return ("(null)");
}

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		if (tok->value)
			free(tok->value);
		if (tok->meta)
			free(tok->meta);
		free(tok);
		tok = tmp;
	}
}

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		if (tok->type == T_WORD)
			printf("[WORD] '%s'\n", safe_val(tok->value));
		else if (tok->type == T_PIPE)
			printf("[PIPE] '%s'\n", safe_val(tok->value));
		else if (tok->type == T_REDIR_IN)
			printf("[<] '%s'\n", safe_val(tok->value));
		else if (tok->type == T_REDIR_OUT)
			printf("[>] '%s'\n", safe_val(tok->value));
		else if (tok->type == T_REDIR_APPEND)
			printf("[>>] '%s'\n", safe_val(tok->value));
		else if (tok->type == T_HEREDOC)
			printf("[<<] '%s'\n", safe_val(tok->value));
		else
			printf("[OTHER] '%s'\n", safe_val(tok->value));
		tok = tok->next;
	}
}

char	**free_split(char **arr, int filled)
{
	int	k;

	if (!arr)
		return (NULL);
	k = 0;
	while (k < filled)
		free(arr[k++]);
	free(arr);
	return (NULL);
}

int	append_repeat(t_wbuild *b, char tag, size_t count)
{
	size_t	k;

	k = 0;
	while (k < count)
	{
		if (!buf_append_char(&b->mbuf, &b->mlen, &b->mcap, tag))
			return (0);
		k++;
	}
	return (1);
}
