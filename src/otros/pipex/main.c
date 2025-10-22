/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:06:58 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:06:58 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Función error de argumentos*/
void	arg_error(void)
{
	ft_putstr_fd("\033[31mError: Bad arguments\n\033[0m", 2);
	ft_putstr_fd("Usage:\t ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	exit(1);
}

/*Función error principal*/
void	ft_error(char *message, int code)
{
	ft_putstr_fd("\033[31mError: \n\033[0m", 2);
	perror(message);
	exit(code);
}

/*Función para verificar si no se pasa comando*/
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

/*Función principal que ejecuta mi pipex*/
int	main(int argc, char **argv, char **envp)
{
	int	exit_code;

	exit_code = 0;
	if (argc == 5)
	{
		if (empty_cmd(argv[2]) || empty_cmd(argv[3]))
			ft_error("pipex: empty or invalid command", 1);
		pipex(argv, envp);
	}
	else
		arg_error();
	return (exit_code);
}
