/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:33 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:07:33 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Función para ejecutar dos comandos conectados por una tubería (pipe)*/
void	pipex(char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_error("pipex: pipe error", 1);
	pid1 = fork();
	if (pid1 == -1)
		ft_error("pipex: first child (fork 1) error", 1);
	if (pid1 == 0)
		first_child_process(argv, envp, fd);
	pid2 = fork();
	if (pid2 == -1)
		ft_error("pipex: second child (fork 2) error", 1);
	if (pid2 == 0)
		second_child_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}

/*Función para ejecutar el proceso del primer hijo*/
void	first_child_process(char **argv, char **envp, int *fd)
{
	int		infile;
	char	**cmd_args;

	(void)envp;
	infile = open_file(argv[1], 0);
	if (infile == -1)
		ft_error("pipex: infile", 1);
	close(fd[0]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	cmd_args = ft_split_with_quotes(argv[2]);
	if (!cmd_args)
		ft_error("pipex: memory allocation error", 1);
	execute_cmd(cmd_args, envp);
	free_paths(cmd_args);
}

/*Función para ejecutar el proceso del segundo hijo*/
void	second_child_process(char **argv, char **envp, int *fd)
{
	int		outfile;
	char	**cmd_args;

	(void)envp;
	outfile = open_file(argv[4], 1);
	if (outfile == -1)
		ft_error("pipex: outfile", 1);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	cmd_args = ft_split_with_quotes(argv[3]);
	if (!cmd_args)
		ft_error("pipex: memory allocation error", 1);
	execute_cmd(cmd_args, envp);
	free_paths(cmd_args);
}
