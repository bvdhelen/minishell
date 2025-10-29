/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:18:22 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/29 14:18:23 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append_cmd(t_cmd **head, t_cmd *node)
{
	t_cmd	*tmp;

	if (!node)
		return (0);
	if (!*head)
	{
		*head = node;
		return (1);
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*nxt;
	size_t	i;

	while (cmd)
	{
		nxt = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		free(cmd);
		cmd = nxt;
	}
}
