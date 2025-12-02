/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:33:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/12 13:33:00 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_middle_child(t_cmd *cmd, int input_fd, char ***envp_addr, int fd[2])
{
	set_child_signals();
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (apply_redirs(cmd))
		exit(1);
	execute_command_direct(cmd, *envp_addr);
	exit(1);
}

int	handle_parent_builtin_middle(t_cmd *cmd, int input_fd, int pipe_write, char ***envp_addr)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			error_exit("dup2", 1);
		close(input_fd);
	}
	if (dup2(pipe_write, STDOUT_FILENO) == -1)
		error_exit("dup2", 1);
	run_parent_builtin_with_redirs(cmd, envp_addr);
	close(pipe_write);
	return (0);
}

int	handle_middle_cmd(t_cmd *cmd, int input_fd, char ***envp_addr)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit("pipe", 1);
	/*if (is_parent_builtin(cmd->argv[0]))
	{
		handle_parent_builtin_middle(cmd, input_fd, fd[1], envp_addr);
		return (fd[0]);
	}*/
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
		run_middle_child(cmd, input_fd, envp_addr, fd);
	close(fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (fd[0]);
}

pid_t	handle_last_cmd(t_cmd *cmd, int input_fd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
	{
		set_child_signals();
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (apply_redirs(cmd))
			exit(1);
		execute_command_direct(cmd, envp);
		exit(1);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (pid);
}

static void	wait_all(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
}

int	execute_pipeline(t_cmd *cmd_list, char ***envp_addr)
{
	t_cmd	*cmd;
	int		input_fd;
	pid_t	last_pid;
	char	**pipe_env;

	if (!cmd_list)
		return (1);
	pipe_env = dup_envp(*envp_addr);
	if (!pipe_env)
		return (1);
	input_fd = STDIN_FILENO;
	cmd = cmd_list;
	while (cmd->next)
	{
		input_fd = handle_middle_cmd(cmd, input_fd, &pipe_env);
		cmd = cmd->next;
	}
	last_pid = handle_last_cmd(cmd, input_fd, pipe_env);
	wait_all(last_pid);
	free_envp(pipe_env);
	return (g_exit_status);
}
