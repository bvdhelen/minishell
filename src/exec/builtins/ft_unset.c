/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:20:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/30 12:34:11 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
