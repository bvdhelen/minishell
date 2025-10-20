/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:13 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:07:13 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Función para ejecutar varios comandos conectados por varias tuberías (pipes)*/
void	pipex_bonus(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;
	int		prev_fd;
	pid_t	last_pid;

	infile = open_file(argv[1], 0);
	if (infile == -1)
		ft_error("pipex: infile", 1);
	outfile = open_file(argv[argc - 1], 1);
	if (outfile == -1)
		ft_error("pipex: outfile", 1);
	prev_fd = infile;
	i = 2;
	while (i < argc - 2)
	{
		prev_fd = handle_middle_cmd(argv[i], prev_fd, envp);
		i++;
	}
	last_pid = handle_last_cmd(argv[i], prev_fd, outfile, envp);
	close(outfile);
	wait_all(last_pid);
}

/*Función para ejecutar los procesos hijos desde el primero hasta el penúltimo*/
int	handle_middle_cmd(char *cmd, int input_fd, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	**cmd_args;

	if (pipe(fd) == -1)
		ft_error("pipex: pipe error", 1);
	pid = fork();
	if (pid == -1)
		ft_error("pipex: fork error", 1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(input_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(input_fd);
		close(fd[1]);
		cmd_args = ft_split_with_quotes(cmd);
		if (!cmd_args)
			ft_error("pipex: memory allocation error", 1);
		execute_cmd(cmd_args, envp);
		free_paths(cmd_args);
	}
	close(fd[1]);
	close(input_fd);
	return (fd[0]);
}

/*Función para ejecutar el último proceso hijo*/
pid_t	handle_last_cmd(char *cmd, int input_fd, int outfile, char **envp)
{
	pid_t	pid;
	char	**cmd_args;

	pid = fork();
	if (pid == -1)
		ft_error("pipex: last fork error", 1);
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(input_fd);
		close(outfile);
		cmd_args = ft_split_with_quotes(cmd);
		if (!cmd_args)
			ft_error("pipex: memory allocation error", 1);
		execute_cmd(cmd_args, envp);
		free_paths(cmd_args);
	}
	close(input_fd);
	return (pid);
}

/*Función para esperar a todos los procesos hijos
y devolver el código de salida del último comando*/
void	wait_all(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid && WIFEXITED(status))
			exit(WEXITSTATUS(status));
		pid = wait(&status);
	}
	exit(1);
}
