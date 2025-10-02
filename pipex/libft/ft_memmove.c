/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:44:39 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 16:34:12 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	temp_dest = (unsigned char *) dest;
	temp_src = (unsigned char *) src;
	if (dest == src)
		return (dest);
	if (temp_dest > temp_src)
	{
		while (n > 0)
		{
			temp_dest[n - 1] = temp_src[n - 1];
			n--;
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}

/*
int	main(void)
{
	const char	src[] = "@bvdhelen! es mi insta";
	char	dest[30];

	ft_memmove(dest, src, 11);
	dest[11] = '\0'; //Añadir caracter nulo al terminar la cadena
	printf("%s", dest);
	return (0);
}
*/