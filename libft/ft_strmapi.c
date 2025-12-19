/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:33:25 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/21 20:55:59 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[len] = '\0';
	return (result);
}
/*#include <stdio.h>
char	my_func(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (ft_toupper(c));
	return (c);
}

int	main(void)
{
	printf("%s",ft_strmapi("hello",my_func));
	return (0);
}*/
