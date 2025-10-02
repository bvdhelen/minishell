/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:53:50 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/07 19:52:39 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr_len = s_len - start;
	if (substr_len > len)
		substr_len = len;
	substr = malloc(substr_len + 1);
	if (substr == NULL)
		return (NULL);
	ft_memcpy(substr, s + start, substr_len);
	substr[substr_len] = '\0';
	return (substr);
}

/*
int	main(void)
{
	char	str[] = "Mi insta es @bvdhelen!\n";
	char	*result;

	result = ft_substr(str, 12, 11);
	if (result != NULL)
	{
		printf("%s", result);
		free (result);
	}
	return (0);
}
*/