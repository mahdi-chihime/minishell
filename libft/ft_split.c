/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:28:03 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/23 12:53:40 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	count;
	int	in;

	count = 0;
	in = 0;
	while (*s)
	{
		if (*s != c && !in)
		{
			in = 1;
			count++;
		}
		else if (*s == c)
			in = 0;
		s++;
	}
	return (count);
}

int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

void	free_all(char **arr, int i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
}

int	fill(char **result, const char *s, char c, int words)
{
	int	i;
	int	len;
	int	pos;

	i = 0;
	pos = 0;
	while (i < words)
	{
		while (s[pos] == c)
			pos++;
		len = word_len(&s[pos], c);
		result[i] = ft_substr(s, pos, len);
		if (!result[i])
		{
			free_all(result, i);
			return (0);
		}
		pos += len;
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!fill(result, s, c, words))
		return (NULL);
	return (result);
}
/*#include <stdio.h>
int main(void)
{
	char **res = ft_split("a,b,c", ',');
	int i = 0;

	while (res && res[i])
	{
		printf("%s\n", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}*/
