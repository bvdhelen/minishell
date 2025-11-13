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

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	size_t			i;
	size_t			total_size;
	unsigned char	*allocated_mem;

	total_size = nmemb * size;
	allocated_mem = malloc (total_size);
	if (!allocated_mem)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		allocated_mem[i] = 0;
		i++;
	}
	return (allocated_mem);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	if (!dest || !src)
		return (NULL);
	if (!dest && !src)
		return (NULL);
	i = 0;
	temp_dest = (unsigned char *) dest;
	temp_src = (const unsigned char *) src;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove_gnl(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;

	if (!dest || !src)
		return (NULL);
	temp_dest = (unsigned char *) dest;
	temp_src = (const unsigned char *) src;
	if (dest == src || n == 0)
		return (dest);
	if (temp_dest > temp_src)
	{
		while (n > 0)
		{
			temp_dest[n - 1] = temp_src[n - 1];
			n--;
		}
	}
	else
		ft_memcpy_gnl(dest, src, n);
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1)
	{
		s1 = ft_calloc_gnl(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	result = malloc (len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy_gnl(result, s1, len1);
	ft_memcpy_gnl(result + len1, s2, len2 + 1);
	result[len1 + len2] = '\0';
	free (s1);
	return (result);
}
