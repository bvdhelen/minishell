/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:59 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:07:59 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Función para recortar la línea, quitando los \n que haya*/
static char	*get_trimmed_line(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
	{
		free(line);
		ft_error("pipex: malloc strtrim error", 1);
	}
	return (trimmed);
}

/*Función para leer las líneas que el usuario mete por pantalla*/
int	heredoc(char *limiter)
{
	int		pipe_fd[2];
	char	*line;
	char	*trimmed;

	if (pipe(pipe_fd) == -1)
		ft_error("pipex: pipe error", 1);
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		trimmed = get_trimmed_line(line);
		if (ft_strcmp(trimmed, limiter) == 0)
		{
			free(line);
			free(trimmed);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
		free(trimmed);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

/*Función para ejecutar varios comandos conectados por varias tuberías (pipes),
pero en vez de infile, usas lo que mete el ususario por pantalla*/
void	pipex_heredoc(int argc, char **argv, char **envp)
{
	int		i;
	int		input;
	int		outfile;
	int		prev_fd;
	pid_t	last_pid;

	input = heredoc(argv[2]);
	outfile = open_file(argv[argc - 1], 2);
	if (outfile == -1)
		ft_error("pipex: outfile", 1);
	prev_fd = input;
	i = 3;
	while (i < argc - 2)
	{
		prev_fd = handle_middle_cmd(argv[i], prev_fd, envp);
		i++;
	}
	last_pid = handle_last_cmd(argv[i], prev_fd, outfile, envp);
	close(outfile);
	wait_all(last_pid);
}
