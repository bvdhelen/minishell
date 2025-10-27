/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/23 11:31:40 by joperez2         ###   ########.fr       */
=======
/*   Updated: 2025/10/23 12:59:22 by eldiaz-c         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
<<<<<<< HEAD
	char	*line;
	t_token	*tok;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
=======
    char 	*line;
	t_token	*tok;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) // Ctrl-D
        {
            printf("exit\n");
            break ;
        }
        if (*line)
            add_history(line);
>>>>>>> refs/remotes/origin/main
		tok = tokenize(line);
		if (tok)
		{
			print_tokens(tok);
			free_tokens(tok);
		}
<<<<<<< HEAD
		free(line);
	}
	return (0);
=======
        // TODO: pasar 'line' al tokenizador / parser
        free(line);
    }
    return (0);
>>>>>>> refs/remotes/origin/main
}
