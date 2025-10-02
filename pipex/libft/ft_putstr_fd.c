/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:53:57 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/03 21:00:23 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
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
}

/*
int	main(void)
{
	FILE	*file;
	char	str[] = "Mi insta es @bvdhelen!";

	ft_putstr_fd(str, 1);
	file = fopen("prueba.txt", "w");
	ft_putstr_fd(str, fileno(file));
	fclose(file);
	return (0);
}
*/