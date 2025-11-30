/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:07:21 by joperez2          #+#    #+#             */
/*   Updated: 2025/11/30 12:20:27 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	next_is_word(t_token *tok)
{
	if (!tok || !tok->next)
		return (0);
	return (tok->next->type == T_WORD && tok->next->value);
}

static int	set_infile(t_cmd *cmd, char *filename)
{
	int	fd;

	if (cmd->infile != -1)
		close(cmd->infile);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	cmd->infile = fd;
	return (1);
}

static int	set_outfile(t_cmd *cmd, char *filename, int append)
{
	int	flags;
	int	fd;

	if (cmd->outfile != -1)
		close(cmd->outfile);
	flags = O_CREAT | O_WRONLY;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	cmd->outfile = fd;
	return (1);
}

int	handle_redir_tokens(t_token **tok, t_cmd *cmd)
{
	t_token	*t;
	char	*name;

	t = *tok;
	if (!next_is_word(t))
	{
		ft_putstr_fd("minishell: syntax error near redirection\n",
			STDERR_FILENO);
		return (0);
	}
	name = t->next->value;
	if (t->type == T_REDIR_IN && !set_infile(cmd, name))
		return (0);
	else if (t->type == T_REDIR_OUT && !set_outfile(cmd, name, 0))
		return (0);
	else if (t->type == T_REDIR_APPEND && !set_outfile(cmd, name, 1))
		return (0);
	else if (t->type == T_HEREDOC && !set_heredoc_infile(cmd, name))
		return (0);
	*tok = t->next->next;
	return (1);
}
