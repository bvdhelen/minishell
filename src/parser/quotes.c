
#include "../../minishell.h"

/* longitud del token sin contar comillas */
static int	get_token_len(const char *s, int i)
{
	int		len;
	char	q;

	while (s[i] && isspace((unsigned char)s[i]))
		i++;
	len = 0;
	while (s[i] && !isspace((unsigned char)s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			while (s[i] && s[i] != q) { len++; i++; }
			if (s[i]) i++;
		}
		else { len++; i++; }
	}
	return (len);
}

/* extrae el token (concatena trozos y quita comillas) */
static char	*extract_shell_word(const char *s, int i)
{
	int		len;
	char	*word;
	int		pos;
	char	q;

	while (s[i] && isspace((unsigned char)s[i]))
		i++;
	len = get_token_len(s, i);
	word = malloc((size_t)len + 1);
	if (!word) return (NULL);
	pos = 0;
	while (s[i] && !isspace((unsigned char)s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			while (s[i] && s[i] != q) { word[pos++] = s[i++]; }
			if (s[i]) i++;
		}
		else word[pos++] = s[i++];
	}
	word[pos] = '\0';
	return (word);
}

/* cuenta tokens respetando comillas */
static int	count_shell_words(const char *s)
{
	int		i;
	int		count;
	char	q;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && isspace((unsigned char)s[i])) i++;
		if (!s[i]) break;
		count++;
		while (s[i] && !isspace((unsigned char)s[i]))
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				q = s[i++];
				while (s[i] && s[i] != q) i++;
				if (s[i]) i++;
			}
			else i++;
		}
	}
	return (count);
}

/* avanza i hasta el final del token actual (incluye comillas) */
static int	advance_token_end(const char *s, int i)
{
	char	q;

	while (s[i] && !isspace((unsigned char)s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i++];
			while (s[i] && s[i] != q) i++;
			if (s[i]) i++;
		}
		else i++;
	}
	return (i);
}

/* split público con comillas (concatena segmentos) */
char	**ft_split_with_quotes(const char *s)
{
	char	**result;
	char	*word;
	int		words;
	int		i;
	int		j;

	if (!s) return (NULL);
	words = count_shell_words(s);
	result = malloc((words + 1) * sizeof(char *));
	if (!result) return (NULL);
	i = 0; j = 0;
	while (j < words)
	{
		while (s[i] && isspace((unsigned char)s[i])) i++;
		word = extract_shell_word(s, i);
		if (!word) return (free_split(result, j));
		result[j++] = word;
		i = advance_token_end(s, i);
	}
	result[j] = NULL;
	return (result);
}
