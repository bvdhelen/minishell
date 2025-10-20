/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:17:44 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 16:25:21 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		len_sub;
	size_t		size;
	char		*result;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	size = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	if (i == size)
		return (ft_strdup(""));
	j = size - 1;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	len_sub = j - i + 1;
	result = ft_substr(s1, i, len_sub);
	if (result == NULL)
		return (NULL);
	return (result);
}

/*
int	main(void)
{
	char	str[] = "    @bvdhelensssssaasa";
	char	set[] = "a s";
	char	*result;

	result = ft_strtrim(str, set);
	if (result != NULL)
	{
		printf("%s", result);
		free (result);
	}
	return (0);
}
*/