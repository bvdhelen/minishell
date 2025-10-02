/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:37:32 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/27 04:04:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>      // Para printf
#include "ft_printf.h" // Para ft_printf

/*
int main()
{
    int i;
	int	j;

    // %c - Imprime un solo carácter
    char c = '@';
    i = ft_printf("%c", c);
    j = printf("%c", c);
    if (i == j) printf("\nCorrecto.\n");

    // %s - Imprime una string
    char *s = "@bvdhelen!";
    i = ft_printf("%s", s);
    j = printf("%s", s);
    if (i == j) printf("\nCorrecto.\n");

    // %p - Imprime un puntero en formato hexadecimal
    void *p = 123456;
    i = ft_printf("%p", &p);
    j = printf("%p", &p);
    if (i == j) printf("\nCorrecto.\n");

    // %d - Imprime un número decimal (base 10)
    int num = 12345;
    i = ft_printf("%d", num);
    j = printf("%d", num);
    if (i == j) printf("\nCorrecto.\n");

    // %i - Imprime un entero en base 10
    int num2 = -123;
    i = ft_printf("%i", num2);
    j = printf("%i", num2);
    if (i == j) printf("\nCorrecto.\n");

    // %u - Imprime un número decimal sin signo
    unsigned int unum = 12345;
    i = ft_printf("%u", unum);
    j = printf("%u", unum);
    if (i == j) printf("\nCorrecto.\n");

    // %x - Imprime un número hexadecimal en minúsculas
    int hex_min = 4074;
    i = ft_printf("%x", hex_min);
    j = printf("%x", hex_min);
    if (i == j) printf("\nCorrecto.\n");

    // %X - Imprime un número hexadecimal en mayúsculas
    int hex_max = 48879;
    i = ft_printf("%X", hex_max);
    j = printf("%X", hex_max);
    if (i == j) printf("\nCorrecto.\n");

    // %% - Imprime el símbolo de porcentaje
    i = ft_printf("%%");
    j = printf("%%");
    if (i == j) printf("\nCorrecto.\n");

    return (0);
}
*/