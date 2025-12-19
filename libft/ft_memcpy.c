/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:49:01 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 09:59:11 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*#include <unistd.h>

void *ft_memcpy(void *dest, const void *src, size_t n);

int main(void)
{
    char src[] = "ABC";
    char dest[4];

    ft_memcpy(dest, src, 4);
    write(1, dest, 4);
    return (0);
}*/
