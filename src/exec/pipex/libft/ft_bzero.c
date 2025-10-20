/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:17:14 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 01:40:33 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

/*
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

int	main(void)
{
	char	buffer[30] = "Hello @bvdhelen";

	ft_bzero (buffer, 6);
	//printf("%s", buffer); NO SE USA PRINTF PORQUE SOLO LEE HASTA EL PRIMER '\0'
	write(1, &buffer, 15);
	return (0);
}
*/
