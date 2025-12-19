/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:15:46 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 14:28:41 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)&((unsigned char *)s)[i]);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int main(void)
{
    char str[] = "abcdef";
    char *res = ft_memchr(str, 'd', 6);
    if (res)
        printf("%s\n", res);
    else
        printf("Not found\n");
    return 0;
}*/
