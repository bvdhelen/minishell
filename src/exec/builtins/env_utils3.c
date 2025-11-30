/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:50:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/30 12:48:35 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Copia envp excluyendo el índice idx */
static char	**copy_env_exclude(char **envp, int idx, int n)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(sizeof(char *) * n);
	if (!new_env)
		return (envp);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (i != idx)
			new_env[j++] = envp[i];
		else
			free(envp[i]);
		i++;
	}
	new_env[j] = NULL;
	free(envp);
	return (new_env);
}

/* Elimina KEY. Devuelve el nuevo envp */
char	**env_unset(char **envp, const char *key)
{
	int		idx;
	int		n;

	if (!envp || !key)
		return (envp);
	idx = env_index(envp, key);
	if (idx == -1)
		return (envp);
	n = count_env(envp);
	return (copy_env_exclude(envp, idx, n));
}
