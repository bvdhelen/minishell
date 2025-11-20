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
