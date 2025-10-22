/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:36:32 by joperez2          #+#    #+#             */
/*   Updated: 2024/10/04 14:31:00 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (s == 0 && d == 0)
		return (0);
	if (s > d)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	while (i < n)
	{
		d[n - 1] = s[n - 1];
		n--;
	}
	return (dest);
}
