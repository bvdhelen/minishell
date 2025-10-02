/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:10:57 by joperez2          #+#    #+#             */
/*   Updated: 2024/10/07 10:26:46 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	t;

	i = ft_strlen(dest);
	j = 0;
	t = ft_strlen(src);
	if (n == 0)
		return (t);
	if (n < i)
		t += n;
	else
		t += i;
	while (src[j] && (i + 1 + j) < n)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (t);
}
