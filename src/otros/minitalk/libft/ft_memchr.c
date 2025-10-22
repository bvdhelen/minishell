/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:37:05 by joperez2          #+#    #+#             */
/*   Updated: 2024/10/07 11:35:31 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *) s;
	while (n)
	{
		if (*ptr == (unsigned char) c)
			return ((void *)&*ptr);
		ptr++;
		n--;
	}
	return (NULL);
}

/*#include <string.h>
#include <stdio.h>

int	main(void)
{
	int c;
	char str[] = "hola";
	char *ptr;
	c = 'l';

	ptr = ft_memchr(str, c, 5);
	printf("%p\n", memchr(str, c, 5));
	if (!ptr)
		printf("(nil)\n");
	else
		printf("%p\n", ptr);
	return (0);
}*/