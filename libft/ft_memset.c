/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:44:07 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/21 14:56:42 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)s;
	while (i < n)
	{
		arr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*#include <stdio.h>
int main(void)
{
    char str[] = "hello";
    ft_memset(str, '*', 3);
    printf("%s\n", str);
    return (0);
}*/
