/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:18:14 by joperez2          #+#    #+#             */
/*   Updated: 2024/10/07 10:37:47 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*i;
	unsigned char	*j;
	size_t			h;

	i = (unsigned char *)s1;
	j = (unsigned char *)s2;
	h = 0;
	while (h < n)
	{
		if (*i != *j)
			return (*i - *j);
		h++;
		i++;
		j++;
	}
	return (0);
}

/*#include <stdio.h>
int	main(void)
{
	const char s1[] = "hol\201";
	const char s2[] = "holA";
	size_t	n = 5;

	printf("%i", ft_memcmp(s1, s2, n));
	return (0);
}*/