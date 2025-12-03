/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_direct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:44:11 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/03 15:44:11 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_builtin_and_exit(t_cmd *cmd, char **envp)
{
	int	code;

	code = execute_child_builtin(cmd, envp);
	exit(code);
}

static void	check_access(char *path, char *cmd)
{
	if (access(path, F_OK) == -1)
		handle_exec_error(path, cmd);
}

static void	check_is_directory(char *path, char *cmd)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		errno = EISDIR;
		handle_exec_error(path, cmd);
	}
}

void	execute_command_direct(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->argv)
		exit(0);
	shift_argv_left_if_needed(cmd);
	if (!cmd->argv[0])
		exit(0);
	if (is_child_builtin(cmd->argv[0]))
		run_builtin_and_exit(cmd, envp);
	path = resolve_path(cmd, envp);
	check_access(path, cmd->argv[0]);
	check_is_directory(path, cmd->argv[0]);
	if (access(path, F_OK) == -1)
	{
		errno = EACCES;
		handle_exec_error(path, cmd->argv[0]);
	}
	execve(path, cmd->argv, envp);
	handle_exec_error(path, cmd->argv[0]);
}
