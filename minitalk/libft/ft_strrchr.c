/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:49:11 by joperez2          #+#    #+#             */
/*   Updated: 2024/10/07 10:51:50 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	j;

	j = (char)c;
	i = (ft_strlen(s));
	while (i >= 0)
	{
		if (s[i] == j)
			return ((char *) &s[i]);
		i--;
	}
	return (NULL);
}

/*#include <stdio.h>
int	main(void)
{
	int c;
	char str[] = "hola";
	char *ptr;
	c = 'z';

	ptr = ft_memchr(str, c, 5);
	if (!ptr)
		printf("NULL\n");
	else
		printf("%s\n", ptr);
	return (0);
}*/