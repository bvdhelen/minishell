/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal_upper.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:44:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/29 16:56:40 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hexadecimal_upper(unsigned long n, int fd)
{
	int		count;
	char	hex_char;

	count = 0;
	hex_char = "0123456789ABCDEF"[n % 16];
	if (n >= 16)
		count += ft_print_hexadecimal_upper (n / 16, fd);
	count += write(fd, &hex_char, 1);
	return (count);
}
