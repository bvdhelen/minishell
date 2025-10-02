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

#include "get_next_line.h"

static int	contains_newline(const char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*fill_buffer(int fd, char *s_buffer)
{
	char	*backup_buffer;
	int		bytes_read;

	backup_buffer = ft_calloc_gnl(1, BUFFER_SIZE + 1);
	if (!backup_buffer)
		return (NULL);
	while (!contains_newline(s_buffer))
	{
		bytes_read = read(fd, backup_buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free (backup_buffer);
			if (bytes_read < 0 || !*s_buffer)
				return (free (s_buffer), NULL);
			return (s_buffer);
		}
		backup_buffer[bytes_read] = '\0';
		s_buffer = ft_strjoin_gnl(s_buffer, backup_buffer);
		if (!s_buffer)
			return (free (backup_buffer), NULL);
	}
	free (backup_buffer);
	return (s_buffer);
}

static char	*extract_line(char *s_buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!s_buffer[i])
		return (NULL);
	while (s_buffer[i] != '\0' && s_buffer[i] != '\n')
		i++;
	line = ft_calloc_gnl(1, i + 2);
	if (!line)
		return (NULL);
	ft_memmove_gnl(line, s_buffer, i);
	if (s_buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	return (line);
}

static char	*remove_extracted_line(char *s_buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (s_buffer[i] != '\0' && s_buffer[i] != '\n')
		i++;
	if (!s_buffer[i])
	{
		free (s_buffer);
		return (NULL);
	}
	new_buffer = ft_calloc_gnl(1, ft_strlen_gnl(s_buffer) - i + 1);
	if (!new_buffer)
	{
		free (s_buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (s_buffer[i] != '\0')
		new_buffer[j++] = s_buffer[i++];
	new_buffer[j] = '\0';
	free (s_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_buffer[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	if (!static_buffer[fd])
		static_buffer[fd] = ft_calloc_gnl(1, BUFFER_SIZE + 1);
	static_buffer[fd] = fill_buffer(fd, static_buffer[fd]);
	if (!static_buffer[fd])
		return (NULL);
	if (!*static_buffer[fd])
	{
		free (static_buffer[fd]);
		static_buffer[fd] = NULL;
		return (NULL);
	}
	line = extract_line(static_buffer[fd]);
	static_buffer[fd] = remove_extracted_line(static_buffer[fd]);
	return (line);
}
