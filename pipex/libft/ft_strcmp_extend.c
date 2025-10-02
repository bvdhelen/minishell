/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_extend.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:40:08 by marvin            #+#    #+#             */
/*   Updated: 2025/07/18 13:40:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
int	main(void)
{
	printf("%d\n", ft_strcmp("hola", "hola"));
	printf("%d\n", ft_strcmp("hola", "holi"));
	printf("%d\n", ft_strcmp("holi", "hola"));
	printf("%d\n", ft_strcmp("hola", "ho"));
	return (0);
}
*/