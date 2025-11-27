/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:26:09 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/25 11:26:09 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_exit(char **argv)
{
	long	code;
	int		i;

	if (!argv[1])
		return (g_exit_status);
	i = 0;
	if (argv[1][i] == '+' || argv[1][i] == '-')
		i++;
	while (argv[1][i])
	{
		if (!ft_isdigit((unsigned char)argv[1][i]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			return (2);
		}
		i++;
	}
	code = ft_atoi(argv[1]);
	return ((unsigned char)code);
}
