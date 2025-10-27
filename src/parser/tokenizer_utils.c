/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:10:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/27 11:55:54 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		if (tok->value) free(tok->value);
		if (tok->meta) free(tok->meta);
		free(tok);
		tok = tmp;
	}
}

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		if (tok->type == T_WORD)
			printf("[WORD] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_PIPE)
			printf("[PIPE] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_REDIR_IN)
			printf("[<] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_REDIR_OUT)
			printf("[>] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_REDIR_APPEND)
			printf("[>>] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_HEREDOC)
			printf("[<<] '%s'\n", tok->value ? tok->value : "(null)");
		else
			printf("[OTHER] '%s'\n", tok->value ? tok->value : "(null)");
		tok = tok->next;
	}
}

char	**free_split(char **arr, int filled)
{
	int	k;

	if (!arr) return (NULL);
	k = 0;
	while (k < filled) { free(arr[k]); k++; }
	free(arr);
	return (NULL);
}
