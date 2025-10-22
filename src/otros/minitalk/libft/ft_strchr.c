/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:48:08 by joperez2          #+#    #+#             */
/*   Updated: 2024/10/07 10:22:53 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	j;

	j = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == j)
			return ((char *)&s[i]);
		i++;
	}
	if (j == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
