/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:05:31 by joperez2          #+#    #+#             */
/*   Updated: 2025/02/26 10:59:38 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uputnbr_pf(unsigned int n, int *count)
{
	long	nbr;

	nbr = n;
	if (nbr >= 10)
		ft_uputnbr_pf(nbr / 10, count);
	*count += ft_putchar_pf((nbr % 10) + 48);
	return (*count);
}

static int	what_type(char const str, va_list params)
{
	int	count;

	count = 0;
	if (str == 'c')
		count += ft_putchar_pf(va_arg(params, int));
	else if (str == 's')
		count += ft_putstr_pf(va_arg(params, char *));
	else if (str == 'd' || str == 'i')
		ft_putnbr_pf(va_arg(params, int), &count);
	else if (str == 'u')
		ft_uputnbr_pf(va_arg(params, unsigned int), &count);
	else if (str == 'x')
		ft_hex_pf(va_arg(params, unsigned int), 0, &count);
	else if (str == 'X')
		ft_hex_pf(va_arg(params, unsigned int), 1, &count);
	else if (str == 'p')
		ft_print_pointer_pf(va_arg(params, unsigned long long), &count);
	else if (str == '%')
		count += ft_putchar_pf('%');
	else
		return (-1);
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	params;
	int		count;
	int		result;
	int		s_index;

	count = 0;
	s_index = 0;
	va_start(params, str);
	while (str[s_index])
	{
		if (str[s_index] == '%')
		{
			s_index++;
			if (!str[s_index])
				break ;
			result = what_type(str[s_index], params);
			if (result == -1)
				return (va_end(params), -1);
			count += result;
		}
		else
			count += ft_putchar_pf(str[s_index]);
		s_index++;
	}
	return (va_end(params), count);
}
