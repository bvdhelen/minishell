/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:48:27 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/23 13:48:27 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_slash(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*resolve_path(t_cmd *cmd, char **envp)
{
	char	*path;

	if (has_slash(cmd->argv[0]))
		return (ft_strdup(cmd->argv[0]));
	path = get_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	return (path);
}

static void	handle_exec_error(char *path, char *cmd)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		free(path);
		exit(126);
	}
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(path);
		exit(127);
	}
	perror("minishell");
	free(path);
	exit(1);
}

void	execute_command_direct(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(0);
	path = resolve_path(cmd, envp);
	if (access(path, F_OK) == -1)
		handle_exec_error(path, cmd->argv[0]);
	if (access(path, X_OK) == -1)
	{
		errno = EACCES;
		handle_exec_error(path, cmd->argv[0]);
	}
	execve(path, cmd->argv, envp);
	handle_exec_error(path, cmd->argv[0]);
}

int	execute_command(t_cmd *cmd, char ***envp_addr)
{
	pid_t	pid;
	int		status;
	int		is_builtin;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	is_builtin = is_child_builtin(cmd->argv[0]);
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
	{
		set_child_signals();
		if (is_builtin)
			exit(execute_child_builtin(cmd, *envp_addr));
		execute_command_direct(cmd, *envp_addr);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
