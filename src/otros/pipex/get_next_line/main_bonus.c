/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:37:32 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/27 04:04:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> // Para open()
#include <stdio.h> // Para printf() y perror()
#include <unistd.h> // Para close()
#include "get_next_line_bonus.h"

/*
int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;

	fd1 = open("tests/el_principito.txt", 0);
	if (fd1 == 0)
		return (0);
	fd2 = open("tests/4lines.txt", 0);
	if (fd2 == 0)
		return (0);
	fd3 = open("tests/l3c.txt", 0);
	if (fd3 == 0)
		return (0);
	while ((line = get_next_line(fd1))
		|| (line = get_next_line(fd2))
		|| (line = get_next_line(fd3)))
	{
		printf("%s", line);
		free (line);
	}
	close (fd1);
	close (fd2);
	close (fd3);
	return (0);
}
*/