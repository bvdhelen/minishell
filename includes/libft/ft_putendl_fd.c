/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:34:30 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/03 21:02:19 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

/*
int	main(void)
{
	FILE	*file;
	char	str[] = "Mi insta es @bvdhelen!";

	ft_putendl_fd(str, 1);
	file = fopen("prueba.txt", "w");
	ft_putendl_fd(str, fileno(file));
	fclose(file);
	return (0);
}
*/