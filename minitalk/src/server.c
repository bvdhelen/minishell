/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperez-a <pperez-a@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:46:12 by joperez2          #+#    #+#             */
/*   Updated: 2025/03/12 18:33:30 by pperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

volatile sig_atomic_t	g_len_received = 0;

void	get_char(int signum, int *len, char **str, siginfo_t *info)
{
	static int	current_bit;
	static int	char_value;
	static int	i;

	if (signum == SIGUSR1)
		char_value |= (1 << current_bit);
	current_bit++;
	if (current_bit == CHAR_BIT)
	{
		(*str)[i++] = (char)char_value;
		current_bit = 0;
		char_value = 0;
		if (i == *len)
		{
			ft_printf("%s\n", *str);
			i = 0;
			g_len_received = 0;
			free(*str);
			*str = NULL;
			kill(info->si_pid, SIGUSR2);
			return ;
		}
	}
	kill(info->si_pid, SIGUSR1);
}

void	get_len(int signum, int *len, char **str, siginfo_t *info)
{
	static int	current_bit = 0;

	if (signum == SIGUSR1)
		*len |= (1 << current_bit);
	current_bit++;
	if (current_bit == 32)
	{
		*str = ft_calloc(*len + 1, 1);
		if (!*str)
			return ;
		g_len_received = 1;
		current_bit = 0;
		kill(info->si_pid, SIGUSR2);
	}
	kill(info->si_pid, SIGUSR1);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	len;
	static char	*str = NULL;

	(void)context;
	if (g_len_received == 0)
		get_len(signum, &len, &str, info);
	else
		get_char(signum, &len, &str, info);
}

int	main(void)
{
	t_sigact	sigact;

	sigact.sa_sigaction = signal_handler;
	sigact.sa_flags = SA_SIGINFO;
	ft_printf("Welcome to Jorge's minitalk server!\nPID: %d\n", getpid());
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		return (ft_printf("Error registering SIGUSR1 handler\n"), 1);
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		return (ft_printf("Error registering SIGUSR2 handler\n"), 1);
	while (1)
		pause();
	return (0);
}
