/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:23:18 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/03 20:56:18 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
int	main(void)
{
	FILE	*file;

	ft_putchar_fd('A', 1);

	file = fopen("prueba.txt", "w");
	ft_putchar_fd('@', fileno(file));
	fclose(file);
	return (0);
}
*/