/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:33:02 by joperez2          #+#    #+#             */
/*   Updated: 2025/10/27 11:56:31 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_var_first(int c)
{
	if (c == '_' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_var_next(int c)
{
	if (is_var_first(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*lookup_env(const char *name, char **envp)
{
	size_t	nlen;

	nlen = strlen(name);
	while (envp && *envp)
	{
		if (!strncmp(*envp, name, nlen) && (*envp)[nlen] == '=')
			return (ft_strndup(*envp + nlen + 1, strlen(*envp + nlen + 1)));
		envp++;
	}
	return (ft_strndup("", 0));
}

int	expand_tokens(t_token *head, char **envp, int last_status)
{
	char	*nw;

	while (head)
	{
		if (head->type == T_WORD && head->value)
		{
			nw = expand_word(head->value, head->meta, envp, last_status);
			if (!nw) return (0);
			free(head->value);
			head->value = nw;
		}
		head = head->next;
	}
	return (1);
}
