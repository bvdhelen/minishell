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

void	run_middle_child(t_cmd *cmd, int input_fd, char ***envp_addr, int fd[2])
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

int	handle_parent_builtin_middle(t_cmd *cmd,
	int input_fd, int pipe_write, char ***envp_addr)
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

void	wait_all(pid_t last_pid)
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
