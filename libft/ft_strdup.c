/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:39:28 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/20 15:44:15 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup;

	i = 0;
	while (s[i])
		i++;
	dup = (char *)malloc(i + 1);
	if (!dup)
		return (0);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*#include <stdio.h>

int main(void)
{
    char *src = "hello, mahdi";
    char *copy = ft_strdup(src);

    if (copy)
        printf("%s", copy);
    return (0);
}*/
