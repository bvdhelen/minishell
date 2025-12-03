/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:04:06 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/12/03 14:04:06 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_pipeline(t_cmd *cmd_list, char ***envp_addr)
{
	t_cmd	*cmd;
	int		input_fd;
	pid_t	last_pid;
	char	**pipe_env;

	if (!cmd_list)
		return (1);
	pipe_env = dup_envp(*envp_addr);
	if (!pipe_env)
		return (1);
	input_fd = STDIN_FILENO;
	cmd = cmd_list;
	while (cmd->next)
	{
		input_fd = handle_middle_cmd(cmd, input_fd, &pipe_env);
		cmd = cmd->next;
	}
	last_pid = handle_last_cmd(cmd, input_fd, pipe_env);
	wait_all(last_pid);
	free_envp(pipe_env);
	return (g_exit_status);
}

static void	child_process(t_cmd *cmd, char **envp)
{
	set_child_signals();
	if (apply_redirs(cmd))
		exit(1);
	if (is_child_builtin(cmd->argv[0]))
		exit(execute_child_builtin(cmd, envp));
	execute_command_direct(cmd, envp);
}

int	execute_command(t_cmd *cmd, char ***envp_addr)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->argv)
		return (0);
	shift_argv_left_if_needed(cmd);
	if (!cmd->argv[0])
		return (0);
	pid = fork();
	if (pid == -1)
		error_exit("fork", 1);
	if (pid == 0)
		child_process(cmd, *envp_addr);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
