/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:10:57 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:10:57 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Función para abrir archivos*/
int	open_file(const char *file, int access_mode)
{
	int	fd;

	if (access_mode == 0)
		fd = open(file, O_RDONLY);
	if (access_mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (access_mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (access_mode == -1)
		ft_error("pipex: invalid access mode error", 1);
	return (fd);
}

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

/*Función para ejecutar un comando
127 -> código de error comando no encontrado
ENOENT -> código de error no existe el archivo o directorio*/
void	execute_cmd(char **cmd, char **envp)
{
	char	*path;

	path = check_direct_path(cmd[0]);
	if (!path)
		path = get_cmd_path(cmd[0], envp);
	if (!path)
	{
		free_paths(cmd);
		ft_error("pipex: command not found in PATH", 127);
	}
	check_access(path, cmd);
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_paths(cmd);
		if (errno == ENOENT)
			ft_error("pipex: no such a file or directory", 127);
		else
			ft_error("pipex: execve error", 1);
	}
}
