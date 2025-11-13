/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:47:54 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/13 21:47:54 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Función para concatenar la ruta con el comando*/
char	*join_paths(const char *folder, const char *cmd)
{
	char	*full_path;
	char	*result;

	full_path = ft_strjoin(folder, "/");
	result = ft_strjoin(full_path, cmd);
	free(full_path);
	return (result);
}

/*Función para buscar en los directorios de paths una ruta ejecutable válida
para el comando cmd y la devuelve si la encuentra*/
char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i])
	{
		path = join_paths(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

/*Función para encontrar la ruta del comando (si hay envp o path)*/
char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	path = search_in_paths(paths, cmd);
	free_paths(paths);
	return (path);
}

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
