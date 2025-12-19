/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:49:30 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 11:39:49 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}
/*
#include <unistd.h>
int main(void)
{
    char dest[10];
    const char *src = "hello";

    ft_strlcpy(dest, src, sizeof(dest));
    write(1, dest, 6);
    return (0);
}*/
