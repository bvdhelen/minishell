/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:10:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/15 11:25:57 by eldiaz-c         ###   ########.fr       */
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
