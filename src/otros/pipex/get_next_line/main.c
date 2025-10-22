/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:56:48 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/04/14 20:44:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //libreria read
#include <fcntl.h> //libreria open
#include <stdio.h>
#include "get_next_line.h"

/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests/el_principito.txt", 0);
	if (fd == 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (0);
}
*/