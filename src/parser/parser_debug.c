/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:18:47 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/29 14:18:48 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cmds(t_cmd *cmd)
{
	size_t	n;
	size_t	i;

	n = 0;
	while (cmd)
	{
		printf("CMD#%zu:", ++n);
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf(" argv[%zu]='%s'", i, cmd->argv[i]);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
}
