/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:48:27 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/23 13:48:27 by eldiaz-c         ###   ########.fr       */
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
		error_exit("permission denied error", 126);
	}
}

/*Función para ejecutar un comando
127 -> código de error comando no encontrado
ENOENT -> código de error no existe el archivo o directorio*/
int	execute_command(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	char	*path;
	int		status;

	if (cmd->is_builtin)
		return (execute_builtin(cmd, envp));
	pid = fork();
	if (pid == -1)
		error_exit("fork error", 1);
	if (pid == 0)
	{
		path = check_direct_path(cmd->argv[0], envp);
		if (!path)
			path = get_cmd_path(cmd[0], envp);
		if (!path)
		{
			//error_exit("command not found in PATH", 127);
			fprintf(stderr, "minishell: %s: command not found\n", cmd->argv[0]);
			exit(127);
		}
		check_access(path, cmd);
		if (execve(path, cmd->argv, envp) == -1)
		{
			free(path);
			free_paths(cmd);
			if (errno == ENOENT)
				error_exit("no such a file or directory", 127);
			else
				error_exit("execve error", 1);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}
