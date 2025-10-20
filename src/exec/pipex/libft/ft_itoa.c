/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:38:31 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 16:41:55 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;

	len = ft_count_digits(n);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	if (n == -2147483648)
	{
		ft_memcpy(result, "-2147483648", 12);
		return (result);
	}
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (len > 0 && result[len - 1] != '-')
	{
		len--;
		result[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (result);
}

/*
int	main(void)
{
	int		num;
	char	*result;

	num = 2147483648;
	result = ft_itoa(num);
	if (result != NULL)
	{
		printf("%s", result);
		free (result);
	}
	return (0);
}
*/