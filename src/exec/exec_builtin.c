/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:46:59 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/14 13:46:59 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_parent_builtin_with_redirs(t_cmd *cmd, char ***envp_addr)
{
	int	save_in;
	int	save_out;
	int	status;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in == -1 || save_out == -1)
	{
		perror("minishell: dup");
		if (save_in != -1)
			close(save_in);
		if (save_out != -1)
			close(save_out);
		return (1);
	}
	status = 1;
	if (!apply_redirs(cmd))
		status = execute_parent_builtin(cmd, envp_addr);
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
	return (status);
}

int	is_child_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int	execute_child_builtin(t_cmd *cmd, char **envp)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(envp));
	return (127);
}

int	execute_parent_builtin(t_cmd *cmd, char ***envp_addr)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv, envp_addr));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(cmd->argv, envp_addr));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(cmd->argv, envp_addr));
	return (127);
}
