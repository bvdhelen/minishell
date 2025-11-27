/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:29:50 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/27 14:45:18 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

static void	exit_shell(char **envp)
{
	rl_clear_history();
	free_envp(envp);
	exit(g_exit_status);
	//ft_exit();
}

static void	handle_eof(char **envp)
{
	ft_putstr_fd("\033[0;31mexit\033[0m\n", 1);
	exit_shell(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**shell_env;

	(void)argc;
	(void)argv;
	shell_env = init_env(envp);
	set_interactive_signals();
	while (1)
	{
		line = readline("\033[0;90mminishell$ \033[0m");
		if (!line)
			handle_eof(shell_env);
		if (*line)
		{
			add_history(line);
			if (handle_line(line, &shell_env))
			{
				free(line);
				handle_eof(shell_env);
			}
		}
		free(line);
	}
	return (0);
}
