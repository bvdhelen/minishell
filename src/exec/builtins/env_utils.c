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

static void	free_envp_partial(char **new, int i)
{
	while (i-- > 0)
		free(new[i]);
	free(new);
}

static char	**alloc_empty_envp(void)
{
	char	**new;

	new = malloc(sizeof(char *));
	if (!new)
		return (NULL);
	new[0] = NULL;
	return (new);
}

/*Función que duplica un envp (matriz de strings) en memoria nueva*/
char	**dup_envp(char **envp)
{
	int		i;
	char	**new;

	if (!envp)
		return (alloc_empty_envp());
	i = 0;
	while (envp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i])
		{
			free_envp_partial(new, i);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

/*Función que valida el identificador:
Empieza por '_' o letra*/
int	valid_identifier(const char *s)
{
	int	i;

	if (!s)
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
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
