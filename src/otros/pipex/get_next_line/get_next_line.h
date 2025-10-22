/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:43:27 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/04/20 19:17:09 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	*ft_memmove_gnl(void *dest, const void *src, size_t n);
void	*ft_memcpy_gnl(void *dest, const void *src, size_t n);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
size_t	ft_strlen_gnl(const char *s);

#endif
