/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:33:25 by mchihime          #+#    #+#             */
/*   Updated: 2025/11/02 13:02:39 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*joined;
	size_t	l1;
	size_t	l2;
	size_t	j;

	i = 0;
	j = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	joined = malloc(l1 + l2 + 1);
	if (!joined)
		return (NULL);
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	return (res);
}
