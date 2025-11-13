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

extern char	**environ;
extern int	g_exit_status;

/*Función para ejecutar los procesos hijos desde el primero hasta el penúltimo*/
static int	handle_middle_cmd(t_cmd *cmd, int input_fd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit("pipe error", 1);
	pid = fork();
	if (pid == -1)
		error_exit("fork error", 1);
	if (pid == 0)
	{
		close(fd[0]);
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_command_direct(cmd, envp);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (fd[0]);
}

/*Función para ejecutar el último proceso hijo*/
static pid_t	handle_last_cmd(t_cmd *cmd, int input_fd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("last fork error", 1);
	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		execute_command_direct(cmd, envp);
		exit(EXIT_FAILURE);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	return (pid);
}

/*Función para esperar a todos los procesos hijos
y devolver el código de salida del último comando*/
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


/*Función para ejecutar una lista enlazada de comandos,
conectándolos con pipes si hay más de uno*/
int		execute_pipeline(t_cmd *cmd_list, char **envp)
{
	t_cmd	*cmd;
	int		input_fd;
	pid_t	last_pid;

	if (!cmd_list)
		return (1);
	input_fd = STDIN_FILENO;
	cmd = cmd_list;
	while (cmd->next)
	{
		input_fd = handle_middle_cmd(cmd, input_fd, envp);
		cmd = cmd->next;
	}
	last_pid = handle_last_cmd(cmd, input_fd, envp);
	wait_all(last_pid);
	return (g_exit_status);
}
