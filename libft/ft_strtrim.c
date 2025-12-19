/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:46:07 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/21 17:26:39 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in(char const *s, char c)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in(set, s1[start]))
		start ++;
	end = start;
	while (s1[end])
		end++;
	while (end > start && is_in(set, s1[end - 1]))
		end--;
	result = malloc(end - start + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (start < end)
		result[i++] = s1[start++];
	result[i] = '\0';
	return (result);
}
/*#include <stdio.h>
int	main(){
	printf("%s",ft_strtrim("aabbcchcidfg","abcdefg"));
	return (0);
}*/
