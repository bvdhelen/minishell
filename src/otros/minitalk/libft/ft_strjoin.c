/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:37:21 by joperez2          #+#    #+#             */
/*   Updated: 2024/10/07 10:49:35 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s1_2;
	int		i;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1) + ft_strlen(s2);
	s1_2 = (char *)malloc(i * sizeof(char) + 1);
	if (!s1_2)
		return (0);
	while (*s1)
		*s1_2++ = *s1++;
	while (*s2)
		*s1_2++ = *s2++;
	*s1_2 = '\0';
	return (s1_2 - i);
}
