/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:07:24 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/07/24 13:07:24 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# define READ_END	0	//index pipe extremo lectura
# define WRITE_END	1	//index pipe extremo escritura

//ORIGNAL PIPEX
int		open_file(const char *file, int access_mode);
char	*join_paths(const char *folder, const char *cmd);
char	*search_in_paths(char **paths, char *cmd);
char	*get_cmd_path(char *cmd, char **envp);
void	execute_cmd(char **cmd, char **envp);

char	**free_memory(char **result, int count);
void	free_paths(char **paths);
int		is_absolute_path(const char *cmd);
char	*check_direct_path(const char *cmd);
void	check_access(char *path, char **cmd);

char	**ft_split_with_quotes(const char *s);

void	pipex(char **argv, char **envp);
void	first_child_process(char **argv, char **envp, int *fd);
void	second_child_process(char **argv, char **envp, int *fd);

//BONUS PIPEX
void	arg_error(int min_args);
void	ft_error(char *message, int code);
int		empty_cmd(const char *cmd);
int		check_empty_cmds(char **argv, int start, int end);
int		main(int argc, char **argv, char **envp);

void	pipex_bonus(int argc, char **argv, char **envp);
int		handle_middle_cmd(char *cmd, int input_fd, char **envp);
pid_t	handle_last_cmd(char *cmd, int input_fd, int outfile, char **envp);
void	wait_all(pid_t last_pid);

int		heredoc(char *limiter);
void	pipex_heredoc(int argc, char **argv, char **envp);

#endif
