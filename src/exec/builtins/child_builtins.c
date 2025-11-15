/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:46:30 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/14 13:46:30 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*Devuelve 1 si argv[i] es un flag valido de -n*/
static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

/*Función que imprime sus argumentos separados por espacios
Si se pasa -n, no añade salto de línea al final
Si no hay argumentos, imprime solo \n
echo siempre devuelve el código de salida 0*/
int ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

/*Función que imprime el cwd usando getcwd(NULL, 0)
Y devuelve el código de salida 0 en éxito, 1 en fallo*/
int	ft_pwd(char **argv)
{
	(void)argv;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_exit("pwd", 1);
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	//ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}

/*Función que imprime cada entry de envp que contenga =
Y devuelve el código de salida 0*/
int	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			//ft_putendl_fd(envp[i], STDOUT_FILENO);
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
