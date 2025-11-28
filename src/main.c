/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:29:50 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/28 12:25:10 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

static char	**init_env(char **envp)
{
	char	**dup;

	dup = dup_envp(envp);
	if (!dup)
		error_exit("minishell: malloc", 1);
	return (dup);
}

int	main(int argc, char **argv, char **envp)
{
	char	**shell_env;

	(void)argc;
	(void)argv;
	shell_env = init_env(envp);
	main_loop(&shell_env);
	free_envp(shell_env);
	return (g_exit_status);
}
