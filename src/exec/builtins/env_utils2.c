/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:49:05 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/30 12:47:52 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Busca el índice de KEY en envp (KEY sin '=') */
int	env_index(char **envp, const char *key)
{
	int		i;
	size_t	key_len;

	if (!envp || !key)
		return (-1);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strlen(envp[i]) > key_len
			&& envp[i][key_len] == '='
			&& ft_strncmp(envp[i], key, key_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* Construye "key=value" */
char	*join_keyvalue(const char *key, const char *value)
{
	char	*s;
	size_t	len;
	size_t	key_len;
	size_t	value_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	if (value)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	len = key_len + 1 + value_len;
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	ft_strlcpy(s, key, len + 1);
	s[key_len] = '=';
	if (value)
		ft_strlcpy(s + key_len + 1, value, value_len + 1);
	else
		s[key_len + 1] = '\0';
	return (s);
}

/* Copia envp y añade un nuevo par al final */
static char	**copy_env_add(char **envp, char *new_pair, int n)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (n + 2));
	if (!new_env)
	{
		free(new_pair);
		return (envp);
	}
	i = 0;
	while (i < n)
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i++] = new_pair;
	new_env[i] = NULL;
	free(envp);
	return (new_env);
}

/* Reemplaza o añade KEY=VALUE. Devuelve el nuevo envp */
char	**env_set(char **envp, const char *key, const char *value)
{
	char	*new_pair;
	int		idx;
	int		n;

	if (!key)
		return (envp);
	new_pair = join_keyvalue(key, value);
	if (!new_pair)
		return (envp);
	idx = env_index(envp, key);
	if (idx != -1)
	{
		free(envp[idx]);
		envp[idx] = new_pair;
		return (envp);
	}
	n = count_env(envp);
	return (copy_env_add(envp, new_pair, n));
}
