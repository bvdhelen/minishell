/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/11/13 21:02:19 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int 	g_exit_status = 0;

int	main(void)
{
	char	*line;
	t_token	*tok;
	t_cmd	*pipe;

	while (1)
	{
		line = readline("\033[0;90mminishell$ \033[0m");
		if (!line)
		{
			printf("\033[0;31mexit\033[0m\n");
			break ;
		}
		if (*line)
			add_history(line);
		tok = tokenize(line);
		if (!tok)
		{
			free(line);
			continue ;
		}
		if (!expand_tokens(tok, environ, 0))
		{
			free_tokens(tok);
			free(line);
			continue ;
		}
		pipe = parse_pipeline(tok);
		if (pipe)
		{
			//print_cmds(pipe);
			if (pipe->next)
				g_exit_status = execute_pipeline(pipe, environ);
			else
				g_exit_status = execute_command(pipe, environ);
			free_cmds(pipe);
		}
		free_tokens(tok);
		free(line);
	}
	return (0);
}
