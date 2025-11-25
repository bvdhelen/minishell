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

/* builtin_env.c
   Implementación corregida de export/unset/env helpers para minishell.
   Incluye:
   - ft_export / ft_unset / print_export
   - env_set, env_unset, env_index
   - dup_envp / free_envp
   - utilidades para ordenar export (sort_env_export)
*/

/*Función que cuenta cuántas entradas tiene envp (sin NULL final)*/
int	count_env(char **envp)
{
	int	i;

	if (!envp)
		return (0);
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/*Función que extrae la longitud de KEY antes del '='*/
int	key_len(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

/*Función que compara las claves de arr[i] y arr[j]
para export (ordenar ASCII por KEY)*/
int	compare_export_keys(char *a, char *b)
{
	int	cmp;
	int	len_a;
	int	len_b;
	int	min_len;

	if (!a || !b)
		return (0);
	len_a = key_len(a);
	len_b = key_len(b);
	if (len_a < len_b)
		min_len = len_a;
	else
		min_len = len_b;
	cmp = ft_strncmp(a, b, min_len);
	if (cmp != 0)
		return (cmp);
	return (len_a - len_b);
}

/*Función de ordenación ASCII (bubblesort) por KEY (antes del '='),
para export sin argumentos*/
void	sort_env_export(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[j] && arr[j + 1])
		{
			if (compare_export_keys(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/*Función que duplica envp y lo ordena por clave
para export*/
char	**duplicate_env_and_sort(char **envp)
{
	char	**copy;

	copy = dup_envp(envp);
	if (!copy)
		return (NULL);
	sort_env_export(copy);
	return (copy);
}

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
