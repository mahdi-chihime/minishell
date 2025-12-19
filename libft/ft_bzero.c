/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:05:03 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 11:05:15 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)s;
	while (i < n)
	{
		arr[i] = 0;
		i++;
	}
}

/*#include <stdio.h>
int main()
{
	char a[] = "hello";
	ft_bzero(a,5);
	printf("%s",a);
	return 0;
}*/
