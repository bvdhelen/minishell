/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:08:53 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/30 12:09:03 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	redirect_if_needed(int fd, int stdfd)
{
	if (fd == -1)
		return (0);
	if (dup2(fd, stdfd) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirs(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (redirect_if_needed(cmd->infile, STDIN_FILENO) == -1)
		return (1);
	if (redirect_if_needed(cmd->outfile, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}
