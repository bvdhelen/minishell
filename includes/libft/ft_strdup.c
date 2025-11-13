/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:36:14 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 16:38:57 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*dest;
	size_t			len;

	len = ft_strlen(s);
	dest = malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s, len);
	dest[len] = '\0';
	return (dest);
}

/*
int	main(void)
{
	const char	original[] = "Ya no sé que poner aquí";
	char		*duplicada;

	duplicada = ft_strdup(original);
	if (duplicada == NULL)
	{
		printf("No se pudo duplicar la cadena\n");
		return (1);
	}
	printf("Original: %s\n", original);
	printf("Duplicada: %s\n", duplicada);
	free (duplicada);
	return (0);
}
*/