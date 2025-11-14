/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:46:59 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/14 13:46:59 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Función que ejecuta el builtin y devuelve su código de salida*/
int	execute_builtin(t_cmd *cmd, char **envp)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(envp));
	// if (ft_strcmp(cmd->argv[0], "cd") == 0)
	// 	return (ft_cd(cmd->argv));
	// if (ft_strcmp(cmd->argv[0], "export") == 0)
	// 	return (ft_export(cmd->argv, envp));
	// if (ft_strcmp(cmd->argv[0], "unset") == 0)
	// 	return (ft_unset(cmd->argv, envp));
	// if (ft_strcmp(cmd->argv[0], "exit") == 0)
	// 	return (ft_exit(cmd->argv));
	return (127);
}
