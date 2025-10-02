/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:56:46 by joperez2          #+#    #+#             */
/*   Updated: 2025/02/26 10:59:13 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_pf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_pf(char *str)
{
	int	count;
	int	index;

	if (!str)
		str = "(null)";
	count = 0;
	index = 0;
	while (str[index])
	{
		count += ft_putchar_pf(str[index]);
		index++;
	}
	return (count);
}

int	ft_putnbr_pf(int n, int *count)
{
	long	nbr;

	nbr = n;
	if (n < 0)
	{
		*count += ft_putchar_pf('-');
		nbr *= -1;
	}
	if (nbr >= 10)
		ft_putnbr_pf(nbr / 10, count);
	*count += ft_putchar_pf((nbr % 10) + 48);
	return (*count);
}

int	ft_hex_pf(unsigned long long n, int upcase, int *count)
{
	char	*base;

	if (upcase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		ft_hex_pf(n / 16, upcase, count);
	*count += ft_putchar_pf(base[n % 16]);
	return (*count);
}

int	ft_print_pointer_pf(unsigned long long n, int *count)
{
	if (n == 0)
		*count += ft_putstr_pf("(nil)");
	else
	{
		*count += ft_putstr_pf("0x");
		ft_hex_pf(n, 0, count);
	}
	return (*count);
}
