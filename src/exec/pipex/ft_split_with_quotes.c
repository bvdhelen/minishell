/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:33:06 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/29 10:33:06 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Función que salta un token completo en la cadena, respetando las comillas*/
static int	skip_token(const char *s, int i)
{
	char	quote;

	if (s[i] == '\'' || s[i] == '"')
	{
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
			i++;
		if (s[i] == quote)
			i++;
	}
	else
	{
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (i);
}

/*Función que cuenta cuántas palabras (tokens) hay en la cadena,
respetando las comillas*/
static int	count_shell_words(const char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		count++;
		i = skip_token(s, i);
	}
	return (count);
}

/*Función que calcula la longitud de un token (sin espacios),
respetando las comillas*/
static int	get_token_len(const char *s, int i)
{
	int		len;
	char	quote;

	len = 0;
	if (s[i] == '\'' || s[i] == '"')
	{
		quote = s[i];
		i++;
		while (s[i] && s[i] != quote)
		{
			len++;
			i++;
		}
	}
	else
	{
		while (s[i] && !ft_isspace(s[i]))
		{
			len++;
			i++;
		}
	}
	return (len);
}

/*Función que extrae una palabra (token) de la cadena,
respetando las comillas*/
static char	*extract_shell_word(const char *s, int i)
{
	int		len;
	char	*word;
	char	*trimmed;

	while (s[i] && ft_isspace(s[i]))
		i++;
	len = get_token_len(s, i);
	if (s[i] == '\'' || s[i] == '"')
		i++;
	word = ft_substr(s, i, len);
	if (!word)
		return (NULL);
	trimmed = ft_strtrim(word, "'\"");
	free(word);
	return (trimmed);
}

/*Función que divide una cadena en tokens, respetando las comillas*/
char	**ft_split_with_quotes(const char *s)
{
	char	**result;
	char	*word;
	int		word_count;
	int		i;
	int		j;

	word_count = count_shell_words(s);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		word = extract_shell_word(s, i);
		if (!word)
			return (free_memory(result, j - 1));
		result[j] = word;
		j++;
		i = skip_token(s, i);
	}
	result[j] = NULL;
	return (result);
}
