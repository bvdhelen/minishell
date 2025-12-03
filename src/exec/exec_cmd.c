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

/*Función para eliminar vacíos iniciales de argv*/
static void	shift_argv_left_if_needed(t_cmd *cmd)
{
	int	i;
	int	j;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i] && cmd->argv[i][0] == '\0')
		i++;
	if (i == 0)
		return ;
	j = 0;
	while (cmd->argv[i])
		cmd->argv[j++] = cmd->argv[i++];
	while (cmd->argv[j])
		cmd->argv[j++] = NULL;
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
	if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		free(path);
		exit(126);
	}
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
	DIR		*dir;
	char	*path;
	int		code;

	if (!cmd || !cmd->argv)
		exit(0);
	shift_argv_left_if_needed(cmd);
	if (!cmd->argv[0])
		exit(0);
	if (is_child_builtin(cmd->argv[0]))
	{
		code = execute_child_builtin(cmd, envp);
		exit(code);
	}
	path = resolve_path(cmd, envp);
	if (access(path, F_OK) == -1)
		handle_exec_error(path, cmd->argv[0]);
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		errno = EISDIR;
		handle_exec_error(path, cmd->argv[0]);
	}
	if (access(path, F_OK) == -1)
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

	if (!cmd || !cmd->argv)
		return (0);
	shift_argv_left_if_needed(cmd);
	if (!cmd->argv[0])
		return (0);
	is_builtin = is_child_builtin(cmd->argv[0]);
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
	{
		set_child_signals();
		if (apply_redirs(cmd))
			exit(1);
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
