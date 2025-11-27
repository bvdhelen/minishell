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

static int	ft_isnumeric(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **argv)
{
	long	code;

	if (!argv[1])
	{
		g_exit_status = 0;
		return (1);
	}
	if (!ft_isnumeric(argv[1]))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
		g_exit_status = 2;
		return (1);
	}
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return (0);
	}
	code = ft_atoi(argv[1]);
	g_exit_status = (unsigned char)code;
	return (1);
}
