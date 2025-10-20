/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:40:30 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/27 04:04:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned_fd(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putnbr_unsigned_fd(n / 10, fd);
	}
	count += ft_putchar_fd((n % 10) + '0', fd);
	return (count);
}
