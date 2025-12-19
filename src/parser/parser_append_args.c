/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_append_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:29:56 by rakhaled          #+#    #+#             */
/*   Updated: 2025/12/12 20:26:54 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	args_count(char **args)
{
	size_t	count;

	count = 0;
	if (!args)
		return (0);
	while (args[count])
		count++;
	return (count);
}

int	append_args(char ***dst, char **extra)
{
	size_t	base_len;
	size_t	add_len;
	char	**merged;

	if (!extra)
		return (0);
	base_len = args_count(*dst);
	add_len = args_count(extra);
	merged = malloc(sizeof(char *) * (base_len + add_len + 1));
	if (!merged)
		return (free_split(extra), 1);
	ft_memcpy(merged, *dst, sizeof(char *) * base_len);
	ft_memcpy(merged + base_len, extra, sizeof(char *) * add_len);
	merged[base_len + add_len] = NULL;
	free(*dst);
	free(extra);
	*dst = merged;
	return (0);
}
