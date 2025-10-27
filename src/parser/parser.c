<<<<<<< HEAD
#include "../../includes/minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	push_arg(t_cmd *cmd, const char *word)
{
	size_t	n;
	char	**nv;
	char	*s;
	size_t	i;

	n = 0;
	while (cmd->argv && cmd->argv[n])
		n++;
	nv = malloc(sizeof(char *) * (n + 2));
	if (!nv)
		return (0);
	s = ft_strndup(word, strlen(word));
	if (!s && word && *word)
		return (free(nv), 0);
	i = 0;
	while (i < n)
	{
		nv[i] = cmd->argv[i];
		i++;
	}
	nv[n] = s;
	nv[n + 1] = NULL;
	free(cmd->argv);
	cmd->argv = nv;
	return (1);
}

static int	end_of_cmd(t_token *t)
{
	if (!t)
		return (1);
	if (t->type == T_PIPE)
		return (1);
	return (0);
}

t_cmd	*parse_pipeline(t_token *tok)
{
	t_cmd	*head;
	t_cmd	*cmd;

	head = NULL;
	while (tok)
	{
		if (tok->type == T_PIPE)
			return (free_cmds(head), NULL);
		cmd = new_cmd();
		if (!cmd)
			return (free_cmds(head), NULL);
		while (tok && !end_of_cmd(tok))
		{
			if (tok->type != T_WORD || !push_arg(cmd, tok->value))
				return (free_cmds(head), NULL);
			tok = tok->next;
		}
		if (!cmd->argv || !append_cmd(&head, cmd))
			return (free_cmds(head), NULL);
		if (tok && tok->type == T_PIPE)
			tok = tok->next;
	}
	return (head);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:48:56 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/22 15:48:56 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
>>>>>>> refs/remotes/origin/main
