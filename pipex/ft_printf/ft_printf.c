/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:44:32 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/11/06 19:23:31 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format(va_list args, char format, int fd)
{
	int	count;

	count = 0;
	(void)fd;
	if (format == 'c')
		count += ft_putchar_fd(va_arg(args, int), 1);
	else if (format == 's')
		count += ft_putstr_fd(va_arg(args, char *), 1);
	else if (format == 'p')
		count += ft_print_pointer(va_arg(args, char *), 1);
	else if (format == 'd' || format == 'i')
		count += ft_putnbr_fd(va_arg(args, int), 1);
	else if (format == 'u')
		count += ft_putnbr_unsigned_fd(va_arg(args, unsigned int), 1);
	else if (format == 'x')
		count += ft_print_hexadecimal_lower(va_arg(args, unsigned int), 1);
	else if (format == 'X')
		count += ft_print_hexadecimal_upper(va_arg(args, unsigned int), 1);
	else if (format == '%')
		count += ft_putchar_fd('%', 1);
	else
		count += write(1, &format, 1);
	return (count);
}

int	ft_printf(char const *data, ...)
{
	va_list	args;	
	int		i;
	int		count;

	va_start(args, data);
	i = 0;
	count = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '%')
		{
			i++;
			count += ft_format(args, data[i], 1);
		}
		else
			count += write(1, &data[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
