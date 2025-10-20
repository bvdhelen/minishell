/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:20:35 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 01:34:19 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
char	apply_ft_toupper(unsigned int i, char c)
{
	(void)i;
	return ((char)ft_toupper((int)c));
}

int	main(void)
{
	char	str[] = "mi insta es @bvdhelen!";
	char	*result;

	result = ft_strmapi(str, apply_ft_toupper);
	if (result != NULL)
	{
		printf("%s\n", result);
		free (result);
	}
	return (0);
}
*/