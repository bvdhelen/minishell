/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:08:24 by eldiaz-c          #+#    #+#             */
/*   Updated: 2025/10/23 14:08:24 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Los errores "del sistema" usan perror() con el texto en amarillo */
/* Los errores "de shell" imprimen mensaje manual y salen con su código */
void	error_exit(const char *msg, int code)
{
	//fprintf(stderr, "[DEBUG] error_exit(): %s (code %d)\n", msg, code);
	//fprintf(stderr, "\033[0;33mminishell: \n\033[0m%s\n", msg);
	ft_putstr_fd("\033[0;33mminishell: \033[0m", 2);
	perror(msg);
	exit(code);
}
