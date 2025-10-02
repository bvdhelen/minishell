/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal_lower.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:42:31 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/29 16:56:26 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hexadecimal_lower(unsigned long n, int fd)
{
	int		count;
	char	hex_char;

	count = 0;
	hex_char = "0123456789abcdef"[n % 16];
	if (n >= 16)
		count += ft_print_hexadecimal_lower (n / 16, fd);
	count += write(fd, &hex_char, 1);
	return (count);
}
