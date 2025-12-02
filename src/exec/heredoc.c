/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:00:00 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/02 12:32:05 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
}

static void	set_heredoc_signals(struct sigaction *old_int)
{
	struct sigaction	sa;

	sigaction(SIGINT, NULL, old_int);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_sigint;
	sigaction(SIGINT, &sa, NULL);
}

static int	read_heredoc_loop(int fd, const char *delim)
{
	char				*line;
	struct sigaction	old_int;

	set_heredoc_signals(&old_int);
	g_exit_status = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_exit_status == 130)
				return (sigaction(SIGINT, &old_int, NULL), 0);
			break ;
		}
		if (!ft_strcmp(line, delim))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	sigaction(SIGINT, &old_int, NULL);
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
