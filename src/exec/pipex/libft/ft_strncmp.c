/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:38:21 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/03 18:50:15 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
int	main(void)
{
	const char		str1[] = "hello";
	const char		str2[] = "hell";

	printf ("Compara los primeros 4 chars: %d\n", ft_strncmp(str1, str2, 4));
	printf ("Compara los primeros 5 chars: %d\n", ft_strncmp(str1, str2, 5));
	return (0);
}
*/