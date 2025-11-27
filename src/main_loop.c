/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:29:28 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/27 20:15:53 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_env(char **envp)
{
	char	**dup;

	dup = dup_envp(envp);
	if (!dup)
		error_exit("malloc", 1);
	return (dup);
}

int	execute_commands(t_cmd *cmds, char ***envp_addr)
{
	int		should_exit;
	char	*cmd_name;

	should_exit = 0;
	if (!cmds->argv || !cmds->argv[0])
	{
		free_cmds(cmds);
		return (0);
	}
	cmd_name = cmds->argv[0];
	if (cmds->next)
		g_exit_status = execute_pipeline(cmds, envp_addr);
	else if (is_parent_builtin(cmd_name))
		g_exit_status = execute_parent_builtin(cmds, envp_addr);
	else
		g_exit_status = execute_command(cmds, envp_addr);
	if (!cmds->next && !ft_strcmp(cmd_name, "exit"))
		should_exit = 1;
	free_cmds(cmds);
	return (should_exit);
}

int	handle_line(char *line, char ***envp_addr)
{
	t_token	*tok;
	t_cmd	*cmds;
	int		should_exit;

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
	set_parent_exec_signals();
	should_exit = execute_commands(cmds, envp_addr);
	set_interactive_signals();
	return (should_exit);
}
