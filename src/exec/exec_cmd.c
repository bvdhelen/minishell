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

static int	has_slash(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/*Función para eliminar vacíos iniciales de argv*/
void	shift_argv_left_if_needed(t_cmd *cmd)
{
	int	i;
	int	j;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i] && cmd->argv[i][0] == '\0')
		i++;
	if (i == 0)
		return ;
	j = 0;
	while (cmd->argv[i])
		cmd->argv[j++] = cmd->argv[i++];
	while (cmd->argv[j])
		cmd->argv[j++] = NULL;
}

char	*resolve_path(t_cmd *cmd, char **envp)
{
	char	*path;

	if (has_slash(cmd->argv[0]))
		return (ft_strdup(cmd->argv[0]));
	path = get_cmd_path(cmd->argv[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	return (path);
}

static void	exit_with_error(char *path, char *cmd, char *msg, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(path);
	exit(code);
}

void	handle_exec_error(char *path, char *cmd)
{
	if (errno == EISDIR)
		exit_with_error(path, cmd, ": Is a directory\n", 126);
	if (errno == EACCES)
		exit_with_error(path, cmd, ": Permission denied\n", 126);
	if (errno == ENOENT)
		exit_with_error(path, cmd, ": No such file or directory\n", 127);
	perror("minishell");
	free(path);
	exit(1);
}
