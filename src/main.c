/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/20 12:35:16 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

char	**dup_envp(char **envp)
{
	int		i;
	char	**new;

	if (!envp)
	{
		new = malloc(sizeof(char *));
		if (!new)
			return (NULL);
		new[0] = NULL;
		return (new);
	}
	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			while (i > 0)
			{
				free(new[i]);
				i--;
			}
			free(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_copy;
	char	*line;
	t_token	*tok;
	t_cmd	*cmd_list;

	(void)argc;
	(void)argv;
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
