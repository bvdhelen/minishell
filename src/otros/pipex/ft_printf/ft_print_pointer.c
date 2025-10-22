/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:55:35 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/27 04:03:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(void *ptr, int fd)
{
	int	count;

	count = 0;
	if (!ptr)
		return (write(fd, "(nil)", 5));
	count += write(fd, "0x", 2);
	count += ft_print_hexadecimal_lower((unsigned long)ptr, fd);
	return (count);
}
