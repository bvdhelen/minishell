#include "../../minishell.h"

void	free_tokens(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		if (tok->value)
			free(tok->value);
		free(tok);
		tok = tmp;
	}
}

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		if (tok->type == T_WORD)
			printf("[WORD] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_PIPE)
			printf("[PIPE] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_REDIR_IN)
			printf("[<] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_REDIR_OUT)
			printf("[>] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_REDIR_APPEND)
			printf("[>>] '%s'\n", tok->value ? tok->value : "(null)");
		else if (tok->type == T_HEREDOC)
			printf("[<<] '%s'\n", tok->value ? tok->value : "(null)");
		else
			printf("[OTHER] '%s'\n", tok->value ? tok->value : "(null)");
		tok = tok->next;
	}
}

char	**free_split(char **arr, int filled)
{
	int	k;

	if (!arr)
		return (NULL);
	k = 0;
	while (k < filled)
	{
		free(arr[k]);
		k++;
	}
	free(arr);
	return (NULL);
}
