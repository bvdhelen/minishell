/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:18:35 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/04/14 20:37:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char limit)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if ((i == 0 && str[i] != limit)
			|| (str[i] != limit && str[i - 1] == limit))
			count++;
		i++;
	}
	return (count);
}

static char	**free_memory(char **result, int count)
{
	while (count >= 0)
	{
		free (result[count]);
		count--;
	}
	free (result);
	return (NULL);
}

static int	count_letters(char const *str, char limit)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != limit)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		len_word;
	int		word_count;
	int		i;
	int		j;

	word_count = count_words(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		len_word = count_letters(&s[i], c);
		result[j] = ft_substr(s, i, len_word);
		if (result[j] == NULL)
			return (free_memory(result, j - 1));
		i = i + len_word;
		j++;
	}
	result[j] = NULL;
	return (result);
}
