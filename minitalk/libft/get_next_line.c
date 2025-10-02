/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:08:01 by joperez2          #+#    #+#             */
/*   Updated: 2025/03/10 12:24:30 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_gnl(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static char	*read_file_gnl(char *doc, int fd)
{
	char	*file_cpy;
	int		read_bytes;

	read_bytes = 1;
	file_cpy = malloc(BUFFER_SIZE + 1);
	if (!file_cpy)
		return (ft_free_gnl(&doc));
	file_cpy[0] = 0;
	while (read_bytes > 0 && !ft_strchr_gnl(file_cpy, '\n'))
	{
		read_bytes = read(fd, file_cpy, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			file_cpy[read_bytes] = 0;
			doc = ft_strjoin_gnl(doc, file_cpy);
		}
	}
	free(file_cpy);
	if (read_bytes < 0)
		return (ft_free_gnl(&doc));
	return (doc);
}

static char	*gnl_aux(char *doc)
{
	char	*next;
	char	*tmp;
	int		len;

	tmp = ft_strchr_gnl(doc, '\n');
	if (!tmp)
	{
		next = NULL;
		return (ft_free_gnl(&doc));
	}
	else
		len = (tmp - doc) + 1;
	if (!doc[len])
		return (ft_free_gnl(&doc));
	next = ft_substr_gnl(doc, len, ft_strlen_gnl(doc) - len);
	ft_free_gnl(&doc);
	if (!next)
		return (NULL);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*doc[1024];
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!doc[fd] || !ft_strchr_gnl(doc[fd], '\n'))
		doc[fd] = read_file_gnl(doc[fd], fd);
	if (!doc[fd])
		return (NULL);
	tmp = ft_strchr_gnl(doc[fd], '\n');
	line = ft_substr_gnl(doc[fd], 0, (tmp - doc[fd]) + 1);
	if (!line)
		return (ft_free_gnl(&doc[fd]));
	doc[fd] = gnl_aux(doc[fd]);
	return (line);
}
