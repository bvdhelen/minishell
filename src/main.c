/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/20 14:56:03 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	**envp_copy;
	char	*line;
	t_token	*tok;
	t_cmd	*cmd_list;

	(void)argv;
	if (argc != 1)
	{
		printf("Usage: \t\033[0;90m./minishell\033[0m\n");
		return (1);
	}
	envp_copy = dup_envp(envp);
	if (!envp_copy)
		return (1);
	while (1)
	{
		line = readline("\033[0;90mminishell$ \033[0m");
		if (!line)
		{
			printf("\033[0;31mexit\033[0m\n");
			break ;
		}
		if (*line)
			add_history(line);
		tok = tokenize(line);
		if (!tok)
		{
			free(line);
			continue ;
		}
		if (!expand_tokens(tok, envp_copy, g_exit_status))
		{
			free_tokens(tok);
			free(line);
			continue ;
		}
		cmd_list = parse_pipeline(tok);
		if (cmd_list)
		{
			if (cmd_list->next)
				g_exit_status = execute_pipeline(cmd_list, &envp_copy);
			else
				g_exit_status = execute_command(cmd_list, &envp_copy);
			free_cmds(cmd_list);
		}
		free_tokens(tok);
		free(line);
	}
	free_envp(envp_copy);
	if (g_exit_status > 255)
		return (g_exit_status % 256);
	return (g_exit_status);
}
