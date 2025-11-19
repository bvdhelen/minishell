/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:54:25 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/19 14:54:25 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Busca el índice de KEY en envp (KEY sin '=')
Devuelve -1 si no existe */

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
		if (ft_strlen(envp[i]) > key_len && envp[i][key_len] == '='
			&& ft_strncmp(envp[i], key, key_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* Función que construye "key=value" */
static char	*join_keyvalue(const char *key, const char *value)
{
	char	*s;
	size_t	len;
	size_t	key_len;
	size_t	value_len;

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

/* Función que reemplaza o añade KEY=VALUE
Devuelve el nuevo envp */
char	**env_set(char **envp, const char *key, const char *value)
{
	char	**new_env;
	char	*new_pair;
	int		idx;
	int		n;
	int		i;

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
	n = 0;
	while (envp && envp[n])
		n++;
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

/* Función que elimina KEY
Devuelve un nuevo envp */
char	**env_unset(char **envp, const char *key)
{
	char	**new_env;
	int		idx;
	int		n;
	int		i;
	int		j;

	idx = env_index(envp, key);
	if (!envp || idx == -1)
		return (envp);
	n = 0;
	while (envp[n])
		n++;
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

/* Función que valida el identificador:
Empieza por '_' o letra */
int	valid_identifier(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
