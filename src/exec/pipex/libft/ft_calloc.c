/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:46:33 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 16:44:20 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	unsigned char	*allocated_mem;

	total_size = nmemb * size;
	allocated_mem = malloc(total_size);
	if (allocated_mem == NULL)
		return (NULL);
	ft_bzero(allocated_mem, total_size);
	return (allocated_mem);
}

/*
int	main(void)
{
	int		*array;
	size_t	num_elem;
	size_t	i;

	i = 0;
	num_elem = 6;
	array = (int *)ft_calloc(num_elem, sizeof(int));
	if (array == NULL)
	{
		printf("Error al asignar la memoria\n");
		return (1);
	}
	while (i < num_elem)
	{
		printf("array[%zu] = %d\n", i, array[i]);
		i++;
	}
	free (array);
	return (0);
}
*/