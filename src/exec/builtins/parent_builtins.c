/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:46:45 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/14 13:46:45 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_export(char **envp)
{
	int		i;
	char	*eq;

	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (!eq)
		{
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);			
		}
		else
		{
			write(STDOUT_FILENO, envp[i], eq - envp[i] + 1);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(eq + 1, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}

static int	process_assignment(char *arg, char ***envp_addr)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	if (!key)
		return (1);
	value = NULL;
	if (arg[i] == '=')
		value = arg + i + 1;
	if (!valid_identifier(key))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		free(key);
		return (1);
	}
	*envp_addr = env_set(*envp_addr, key, value);
	free(key);
	return (0);
}

int	ft_export(char **argv, char ***envp_addr)
{
	int	i;
	int	status;

	if (!argv[1])
		return (print_export(*envp_addr));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!valid_identifier(argv[i]))
		{
			ft_putstr_fd("export: '", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		else
		{
			if (process_assignment(argv[i], envp_addr) != 0)
				status = 1;
		}
		i++;
	}
	return (status);
}

int	ft_unset(char **argv, char ***envp_addr)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!valid_identifier(argv[i]))
		{
			ft_putstr_fd("unset: '", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		else
			*envp_addr = env_unset(*envp_addr, argv[i]);
		i++;
	}
	return (status);
}

int	ft_cd(char **argv, char ***envp_addr)
{
	int		idx;
	char	*path;
	char	*oldcwd;
	char	*newcwd;

	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
		oldcwd = ft_strdup("");
	if (!argv[1] || argv[1][0] == '\0')
	{
		idx = env_index(*envp_addr, "HOME");
		if (idx == -1)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			free(oldcwd);
			return (1);
		}
		path = ft_strchr((*envp_addr)[idx], '=') + 1;
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldcwd);
		return (1);
	}
	*envp_addr = env_set(*envp_addr, "OLDPWD", oldcwd);
	free(oldcwd);
	newcwd = getcwd(NULL, 0);
	if (newcwd)
	{
		*envp_addr = env_set(*envp_addr, "PWD", newcwd);
		free(newcwd);
	}
	return (0);
}
