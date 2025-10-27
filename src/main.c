/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/27 12:04:12 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

extern char **environ;

int	main(void)
{
	char	*line;
	t_token	*tok;
	t_cmd	*pipe;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line) { printf("exit\n"); break ; }
		if (*line) add_history(line);
		tok = tokenize(line);
		if (!tok) { free(line); continue ; }
		if (!expand_tokens(tok, environ, 0)) { free_tokens(tok); free(line); continue ; }
		pipe = parse_pipeline(tok);
		if (pipe) { print_cmds(pipe); free_cmds(pipe); }
		free_tokens(tok);
		free(line);
	}
	return (0);
}
