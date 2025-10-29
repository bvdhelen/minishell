/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:02:36 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/29 14:20:33 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	main(void)
{
	char	*line;
	t_token	*tok;
	t_cmd	*pipe;

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
			print_cmds(pipe);
			free_cmds(pipe);
		}
		free_tokens(tok);
		free(line);
	}
	return (0);
}
