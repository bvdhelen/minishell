/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:43:02 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/25 11:43:02 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_target_path(char **argv, char **envp, char **path)
{
	int	idx;

	if (argv[1] && argv[1][0] != '\0')
	{
		*path = argv[1];
		return (0);
	}
	idx = env_index(envp, "HOME");
	if (idx == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	*path = ft_strchr(envp[idx], '=') + 1;
	return (0);
}

static void	update_pwd_vars(char ***envp_addr, char *oldcwd)
{
	char	*newcwd;

	*envp_addr = env_set(*envp_addr, "OLDPWD", oldcwd);
	free(oldcwd);
	newcwd = getcwd(NULL, 0);
	if (!newcwd)
		return ;
	*envp_addr = env_set(*envp_addr, "PWD", newcwd);
	free(newcwd);
}

int	ft_cd(char **argv, char ***envp_addr)
{
	char	*path;
	char	*oldcwd;

	oldcwd = getcwd(NULL, 0);
	if (!oldcwd)
		oldcwd = ft_strdup("");
	if (get_target_path(argv, *envp_addr, &path))
	{
		free(oldcwd);
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldcwd);
		return (1);
	}
	update_pwd_vars(envp_addr, oldcwd);
	return (0);
}
