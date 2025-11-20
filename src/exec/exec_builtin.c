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

int	is_child_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env"));
}

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"));
}

/*Función que ejecuta el builtin y devuelve su código de salida*/
// if (!cmd || !cmd->argv || !cmd->argv[0])
	// 	return (1);
int	execute_child_builtin(t_cmd *cmd, char **envp)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(envp));
	return (127);
}

/*Función que ejecuta el builtin y devuelve su código de salida*/
// if (!ft_strcmp(cmd->argv[0], "export"))
//  	return (ft_export(cmd->argv, envp));
// if (!ft_strcmp(cmd->argv[0], "unset"))
// 	return (ft_unset(cmd->argv, envp));
// if (!ft_strcmp(cmd->argv[0], "exit"))
//  	return (ft_exit(cmd->argv));
int	execute_parent_builtin(t_cmd *cmd, char ***envp_addr)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv, envp_addr));
	return (127);
}
