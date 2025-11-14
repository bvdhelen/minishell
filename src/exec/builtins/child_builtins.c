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

/*Función blablabla*/
int ft_echo(char **argv)
{

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
	ft_putendl_fd(cwd, STDOUT_FILENO);
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
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
