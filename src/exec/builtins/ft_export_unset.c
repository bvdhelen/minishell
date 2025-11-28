/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:50:58 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/28 11:51:12 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*Función que imprime export al estilo bash (declare -x KEY=VALUE)*/
int	print_export(char **envp)
{
	int		i;
	char	*eq;
	char	**copy;

	copy = duplicate_env_and_sort(envp);
	if (!copy)
		return (1);
	i = 0;
	while (copy[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		eq = ft_strchr(copy[i], '=');
		if (eq)
		{
			write(STDOUT_FILENO, copy[i], (size_t)(eq - copy[i]));
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(eq + 1, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd(copy[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	free_envp(copy);
	return (0);
}

/*Función que procesa KEY=VALUE o KEY o KEY= (añade o actualiza envp)*/
int	process_assignment(char *arg, char ***envp_addr)
{
	int		i;
	char	*key;
	char	*value;

	if (!arg || !envp_addr)
		return (1);
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

/*builtin export: muestra el env ordenado o añade variables*/
int	ft_export(char **argv, char ***envp_addr)
{
	int	i;
	int	status;

	if (!argv || !envp_addr)
		return (1);
	if (!argv[1])
		return (print_export(*envp_addr));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (process_assignment(argv[i], envp_addr) != 0)
			status = 1;
		i++;
	}
	return (status);
}

/*builtin unset: elimina variables de entorno*/
int	ft_unset(char **argv, char ***envp_addr)
{
	int	i;
	int	status;

	if (!argv || !envp_addr)
		return (1);
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (!valid_identifier(argv[i]) || ft_strchr(argv[i], '=') != NULL)
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
