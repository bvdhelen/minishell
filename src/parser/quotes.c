/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/10/22 15:10:13 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/22 15:10:13 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_quoted(const char *s, int *i, char *w, int *pos)
{
	char	q;

	q = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != q)
	{
		w[*pos] = s[*i];
		(*pos)++;
		(*i)++;
	}
	if (s[*i])
		(*i)++;
}

static void	copy_token(const char *s, int *i, char *w)
{
	int	pos;

	pos = 0;
	while (s[*i] && !isspace((unsigned char)s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
			copy_quoted(s, i, w, &pos);
		else
		{
			w[pos] = s[*i];
			pos++;
			(*i)++;
		}
	}
	w[pos] = '\0';
}

static int	ensure_cap(char ***arr, int *cap, int needed)
{
	char	**new_arr;
	int		i;

	if (needed <= *cap)
		return (1);
	if (*cap == 0)
		*cap = 4;
	while (*cap < needed)
		*cap *= 2;
	new_arr = malloc(sizeof(char *) * (*cap));
	if (!new_arr)
		return (0);
	i = 0;
	while (i < needed - 1)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = new_arr;
	return (1);
}

static int	split_loop(const char *s, char ***res, int *cap, int *count)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i])
	{
		while (s[i] && isspace((unsigned char)s[i]))
			i++;
		if (!s[i])
			break ;
		if (!ensure_cap(res, cap, *count + 1))
			return (0);
		word = malloc(strlen(s + i) + 1);
		if (!word)
			return (0);
		copy_token(s, &i, word);
		(*res)[*count] = word;
		(*count)++;
	}
	return (1);
}

char	**ft_split_with_quotes(const char *s)
{
	char	**res;
	int		cap;
	int		count;

	if (!s)
		return (NULL);
	res = NULL;
	cap = 0;
	count = 0;
	if (!split_loop(s, &res, &cap, &count))
		return (free_split(res, count));
	if (!res)
	{
		res = malloc(sizeof(char *));
		if (!res)
			return (NULL);
		res[0] = NULL;
		return (res);
	}
	res[count] = NULL;
	return (res);
}
