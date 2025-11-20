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

extern int	g_exit_status;

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
void	check_access(char *path)
{
	if (access(path, X_OK) == -1)
	{
		free(path);
		error_exit("permission denied", 126);
	}
}

/*Función para ejecutar un comando directamente (sin fork)
Se usa dentro de los procesos hijos del pipeline*/
/*127 -> código de error comando no encontrado
ENOENT -> código de error no existe el archivo o directorio*/
void	execute_command_direct(t_cmd *cmd, char **envp)
{
	char	*path;

	path = check_direct_path(cmd->argv[0]);
	if (!path)
		path = get_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		fprintf(stderr, "\033[0;35mminishell:\033[0m"
			"%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	check_access(path);
	if (execve(path, cmd->argv, envp) == -1)
	{
		free(path);
		if (errno == ENOENT)
			error_exit("no such a file or directory", 127);
		else if (errno == EACCES)
			error_exit("permission denied", 126);
		else
			error_exit("execve", 1);
	}
}

/*Función principal para ejecutar un comando*/
//printf("[DEBUG] Entrando en execute_command()\n");
//printf("[DEBUG] Estoy en el hijo (PID: %d)\n", getpid());
//printf("[DEBUG] Padre (PID: %d), esperando al hijo...\n", getpid());
//printf("[DEBUG] Salgo de execute_command() con status %d\n", status);
int	execute_command(t_cmd *cmd, char ***envp_addr)
{
	pid_t	pid;
	int		status;

	if (is_parent_builtin(cmd->argv[0]) == 1)
		return (execute_parent_builtin(cmd, envp_addr));
	if (is_child_builtin(cmd->argv[0]) == 1)
	{
		pid = fork();
		if (pid == -1)
			error_exit("fork", 1);
		if (pid == 0)
			exit(execute_child_builtin(cmd, *envp_addr));
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
		execute_command_direct(cmd, *envp_addr);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}
