/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_router.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:26:54 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/30 11:12:29 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_simple_exit(t_cmd *cmds)
{
	if (!cmds || !cmds->argv || !cmds->argv[0])
		return (0);
	if (cmds->next)
		return (0);
	if (ft_strcmp(cmds->argv[0], "exit") != 0)
		return (0);
	return (1);
}

static void	cleanup_and_exit(char ***envp_addr)
{
	rl_clear_history();
	free_envp(*envp_addr);
	exit(g_exit_status);
}

static void	handle_exit_command(t_cmd *cmds, char ***envp_addr)
{
	int	do_exit;

	ft_putstr_fd("exit\n", 1);
	do_exit = ft_exit(cmds->argv);
	free_cmds(cmds);
	if (do_exit)
		cleanup_and_exit(envp_addr);
}

void	execute_commands(t_cmd *cmds, char ***envp_addr)
{
	if (!cmds || !cmds->argv || !cmds->argv[0])
	{
		free_cmds(cmds);
		return ;
	}
	if (is_simple_exit(cmds))
	{
		handle_exit_command(cmds, envp_addr);
		return ;
	}
	if (cmds->next)
		g_exit_status = execute_pipeline(cmds, envp_addr);
	else if (is_parent_builtin(cmds->argv[0]))
		g_exit_status = run_parent_builtin_with_redirs(cmds, envp_addr);
	else
		g_exit_status = execute_command(cmds, envp_addr);
	free_cmds(cmds);
}
