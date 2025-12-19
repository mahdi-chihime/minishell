/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:02:24 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 10:43:42 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (dest == src || n == 0)
		return (dest);
	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
		return (dest);
	}
	while (n > 0)
	{
		n--;
		d[n] = s[n];
	}
	return (dest);
}
/*
#include <unistd.h>
int main(void)
{
    char str[7] = "abcde";

    ft_memmove(str + 1, str, 4);
    write(1, str, 6);
    return (0);
}*/
