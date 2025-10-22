/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:08:23 by joperez2          #+#    #+#             */
/*   Updated: 2025/03/10 12:24:49 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, int c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (&str[index]);
		index++;
	}
	if (c == 0)
		return (&str[index]);
	return (NULL);
}

static void	*ft_calloc_gnl(size_t count, size_t size)
{
	void			*result;
	unsigned char	*current_position;
	size_t			total_size;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total_size = count * size;
	result = malloc(total_size);
	if (!result)
		return (NULL);
	current_position = (unsigned char *)result;
	while (total_size != 0)
	{
		*current_position = 0;
		current_position++;
		total_size--;
	}
	return (result);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		c;

	if (!s1)
	{
		s1 = malloc(1 + 1);
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	s3 = ft_calloc_gnl(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1, sizeof(char));
	if (!s3)
		return (ft_free_gnl(&s1));
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	c = -1;
	while (s2[++c])
		s3[i + c] = s2[c];
	free(s1);
	return (s3);
}

char	*ft_substr_gnl(char *source, unsigned int start, size_t length)
{
	size_t	index;
	size_t	len;
	char	*memory;

	index = 0;
	len = ft_strlen_gnl(source);
	if (start >= len)
		return (ft_calloc_gnl(1, 1));
	if (length > (len - start))
		length = len - start;
	memory = (char *)malloc(length + 1);
	if (!memory)
		return (NULL);
	while (index < length)
	{
		memory[index] = source[start + index];
		index++;
	}
	memory[index] = 0;
	return (memory);
}
