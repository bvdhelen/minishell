/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eldiaz-c <eldiaz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 00:33:38 by eldiaz-c          #+#    #+#             */
/*   Updated: 2024/10/08 00:38:42 by eldiaz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void	apply_ft_toupper(unsigned int i, char *c)
{
	(void)i;
	*c = (char)ft_toupper((int)*c);
}

int	main(void)
{
	char	str[] = "mi insta es @bvdhelen!";

	ft_striteri(str, apply_ft_toupper);
	printf("%s\n", str);
	return (0);
}
*/