/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:11:08 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:11:08 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Función para liberar la memoria de un array de strings hasta el índice count*/
char	**free_memory(char **result, int count)
{
	while (count >= 0)
	{
		free(result[count]);
		count--;
	}
	free(result);
	return (NULL);
}

/*Función para liberar memoria de las rutas*/
void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/*Función para buscar rutas absolutas o relativas*/
int	is_absolute_path(const char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp("/", cmd, 1) == 0)
		return (1);
	if (ft_strncmp("./", cmd, 2) == 0)
		return (1);
	if (ft_strncmp("../", cmd, 3) == 0)
		return (1);
	return (0);
}

/*Función para comprobar si es una ruta absoluta o relativa*/
char	*check_direct_path(const char *cmd)
{
	if (is_absolute_path(cmd) && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

/*Función para comprobar si el acceso está permitido 
(comando encontrado) pero no ejecutable
código de error 126 -> comando encontrado pero no ejecutable*/
void	check_access(char *path, char **cmd)
{
	if (access(path, X_OK) == -1)
	{
		free(path);
		free_paths(cmd);
		ft_error("pipex: permission denied error", 126);
	}
}
