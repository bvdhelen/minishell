/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:06:51 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:06:51 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*Función error de argumentos*/
void	arg_error(int min_args)
{
	ft_putstr_fd("\033[31mError: Bad arguments\n\033[0m", 2);
	if (min_args == 5)
		ft_putstr_fd(
			"Usage:\t ./pipex <file1> <cmd1> <cmd2> ... <cmdn> <file2>\n", 1);
	if (min_args == 6)
		ft_putstr_fd(
			"Usage:\t ./pipex here_doc LIMITER <cmd1> <cmd2> <file>\n", 1);
	exit(1);
}

/*Función error principal*/
void	ft_error(char *message, int code)
{
	ft_putstr_fd("\033[31mError: \n\033[0m", 2);
	perror(message);
	exit(code);
}

/*Función para verificar si el comando está vacío*/
int	empty_cmd(const char *cmd)
{
	while (*cmd)
	{
		if (!ft_isspace(*cmd))
			return (0);
		cmd++;
	}
	return (1);
}

/*Función para comprobar si hay algún comando vacío*/
int	check_empty_cmds(char **argv, int start, int end)
{
	while (start <= end)
	{
		if (empty_cmd(argv[start]))
			return (1);
		start++;
	}
	return (0);
}

/*Función principal que ejecuta mi pipex*/
int	main(int argc, char **argv, char **envp)
{
	int	exit_code;

	exit_code = 0;
	if (argc < 5)
		arg_error(5);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			arg_error(6);
		if (check_empty_cmds(argv, 3, argc - 2))
			ft_error("pipex: empty or invalid command", 1);
		pipex_heredoc(argc, argv, envp);
	}
	else
	{
		if (check_empty_cmds(argv, 2, argc - 2))
			ft_error("pipex: empty or invalid command", 1);
		if (argc == 5)
			pipex(argv, envp);
		else if (argc > 5)
			pipex_bonus(argc, argv, envp);
	}
	return (exit_code);
}
