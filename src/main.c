/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/23 12:59:22 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
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
		tok = tokenize(line);
		if (tok)
		{
			print_tokens(tok);
			free_tokens(tok);
		}
        // TODO: pasar 'line' al tokenizador / parser
        free(line);
    }
    return (0);
}
