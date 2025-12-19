/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:40:33 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 12:24:07 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest;
	size_t	src_len;

	dest = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dest)
		return (size + src_len);
	i = 0;
	while (src[i] && (dest + i < size - 1))
	{
		dst[dest + i] = src[i];
		i++;
	}
	dst[dest + i] = '\0';
	return (dest + src_len);
}
/*#include <stdio.h>
int main(void)
{
    char dest[15] = "Hello, ";
    const char *src = "world!";

    size_t result = ft_strlcat(dest, src, sizeof(dest));

    printf("%zu", result);
    printf("Final string: %s\n", dest);
    return 0;
}*/
