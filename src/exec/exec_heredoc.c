/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:34:00 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/30 11:44:02 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc_loop(int fd, const char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (1);
}

static int	create_heredoc(const char *delim)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	if (!read_heredoc_loop(fd[1], delim))
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	close(fd[1]);
	return (fd[0]);
}

int	set_heredoc_infile(t_cmd *cmd, const char *delim)
{
	int	fd;

	if (cmd->infile != -1)
		close(cmd->infile);
	fd = create_heredoc(delim);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	cmd->infile = fd;
	return (1);
}
