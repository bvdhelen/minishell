/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joperez2 <joperez2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:49:03 by joperez2          #+#    #+#             */
/*   Updated: 2024/09/19 10:26:12 by joperez2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*#include <stdio.h>

int	main(void)
{
	int	test1;
	int	test2;
	int	test3;
	int	test4;

	test1 = 'H';
	test2 = '!';
	test3 = '9';
	test4 = '0';
	printf("Test 1: %d -> %d\n", test1, ft_isdigit(test1));
	printf("Test 2: %d -> %d\n", test2, ft_isdigit(test2));
	printf("Test 3: %d -> %d\n", test3, ft_isdigit(test3));
	printf("Test 4: %d -> %d\n", test4, ft_isdigit(test4));
	return (0);
}
*/