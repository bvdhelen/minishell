/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperez-a <pperez-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:25:44 by joperez2          #+#    #+#             */
/*   Updated: 2025/03/12 14:39:49 by pperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

void	send_char(int pid, char c)
{
	int	i;
	int	error;
	int	bit;

	i = -1;
	while (++i < CHAR_BIT)
	{
		g_ack_received = 0;
		bit = c & 0x001;
		if (bit)
			error = kill(pid, SIGUSR1);
		else
			error = kill(pid, SIGUSR2);
		if (error == -1)
			return (ft_printf("Error sending signal\n"), exit(1));
		c = c >> 1;
		while (g_ack_received == 0)
			usleep(200);
	}
}

void	send_len(int pid, int len)
{
	int	i;
	int	error;
	int	bit;

	i = -1;
	if (g_ack_received == 2)
		return ;
	while (++i < 32)
	{
		g_ack_received = 0;
		bit = len & 0x01;
		if (bit)
			error = kill(pid, SIGUSR1);
		else
			error = kill(pid, SIGUSR2);
		if (error == -1)
			return (ft_printf("Error sending signal\n"), exit(1));
		len = len >> 1;
		while (g_ack_received == 0)
			usleep(200);
	}
}

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_ack_received = 1;
	if (signum == SIGUSR2)
		g_ack_received = 2;
}

int	main(int ac, char **av)
{
	t_sigact	sigact;
	int			i;
	int			pid;

	if (ac != 3)
		return (ft_printf("Usage: %s [PID] [MESSAGE]\n", av[0]), 1);
	if (!ft_strlen(av[2]))
		return (ft_printf("Message is empty!\n"), 1);
	pid = ft_atoi(av[1]);
	sigact.sa_handler = signal_handler;
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		return (ft_printf("Error registering SIGUSR1 handler\n"), 1);
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		return (ft_printf("Error registering SIGUSR2 handler\n"), 1);
	send_len(pid, ft_strlen(av[2]));
	i = 0;
	while (g_ack_received != 2)
		send_char(pid, av[2][i++]);
	return (0);
}
