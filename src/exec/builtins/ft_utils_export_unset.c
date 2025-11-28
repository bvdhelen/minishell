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
