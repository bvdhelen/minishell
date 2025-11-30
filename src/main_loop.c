/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:29:28 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/30 12:19:48 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_eof(char **envp)
{
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	free_envp(envp);
	exit(g_exit_status);
}

static int	handle_line(char *line, char ***envp_addr)
{
	t_token	*tok;
	t_cmd	*cmds;

	tok = tokenize(line);
	if (!tok)
		return (0);
	if (!expand_tokens(tok, *envp_addr, g_exit_status))
	{
		free_tokens(tok);
		return (0);
	}
	cmds = parse_pipeline(tok);
	free_tokens(tok);
	if (!cmds)
		return (0);
	execute_commands(cmds, envp_addr);
	return (1);
}

void	main_loop(char ***envp_addr)
{
	char	*line;

	set_interactive_signals();
	while (1)
	{
		line = readline("\033[0;90mminishell$ \033[0m");
		if (!line)
			handle_eof(*envp_addr);
		if (*line)
		{
			add_history(line);
			if (!handle_line(line, envp_addr))
			{
				free(line);
				continue ;
			}
		}
		free(line);
	}
}
