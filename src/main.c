/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/22 15:12:05 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    char *line;

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

        // TODO: pasar 'line' al tokenizador / parser
        free(line);
    }
    return (0);
}
