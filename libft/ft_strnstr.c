/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:57:59 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 15:08:17 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] && big[i + j] == little[j] && (i + j) < len)
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int main(void)
{
    char arr[] = "hi i am mahdi";
    char *x = ft_strnstr(arr, "a", 15);
    if (x)
        printf("%s\n", x);
    else
        printf("Not found\n");
    return 0;
}*/
