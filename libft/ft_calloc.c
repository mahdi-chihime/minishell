/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:27:04 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/23 15:11:30 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total;
	size_t	i;
	char	*tmp;

	if (nmemb != 0 && size > 4294967295 / nmemb)
		return (NULL);
	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	tmp = (char *)ptr;
	i = 0;
	while (i < total)
	{
		tmp[i] = 0;
		i++;
	}
	return (ptr);
}
/*#include <stdio.h>

int main(void)
{
    char *arr = ft_calloc(1000000000, 1000000000);
    if (arr)
        printf("First byte: %d\n", arr[0]);
    return 0;
}
*/
