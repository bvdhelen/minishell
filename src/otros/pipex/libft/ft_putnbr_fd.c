/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:45:04 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/04/13 17:06:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd((n % 10) + '0', fd);
}

/*
int	main(void)
{
	FILE	*file;
	int		num;

	num = -1234567890;
	ft_putnbr_fd(num, 1);
	file = fopen("prueba.txt", "w");
	ft_putnbr_fd(num, fileno(file));
	fclose(file);
	return (0);
}
*/