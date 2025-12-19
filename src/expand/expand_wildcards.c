/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 13:11:11 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/11 17:27:18 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_pattern(const char *name, const char *pat)
{
	while (*pat)
	{
		if (*pat == '*')
		{
			pat++;
			if (!*pat)
				return (1);
			while (*name)
			{
				if (match_pattern(name, pat))
					return (1);
				name++;
			}
			return (0);
		}
		else if (*name != *pat)
			return (0);
		name++;
		pat++;
	}
	return (*name == 0 && *pat == 0);
}

int	store_word(char ***arr, const char *word)
{
	int		len;
	char	**new;
	char	*dup;

	len = 0;
	while (*arr && (*arr)[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (1);
	if (*arr && len > 0)
		ft_memcpy(new, *arr, sizeof(char *) * len);
	dup = ft_strdup(word);
	if (!dup)
	{
		free(new);
		return (1);
	}
	new[len] = dup;
	new[len + 1] = NULL;
	free(*arr);
	*arr = new;
	return (0);
}

int	match_dir_entries(const char *pattern, char ***out)
{
	DIR				*dir;
	struct dirent	*entry;
	int				matched;

	dir = opendir(".");
	if (!dir)
		return (-1);
	matched = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_name[0] != '.' && match_pattern(entry->d_name, pattern))
		{
			if (store_word(out, entry->d_name))
			{
				closedir(dir);
				return (-1);
			}
			matched++;
		}
	}
	closedir(dir);
	return (matched);
}

int	add_entry(char *arg, char ***out)
{
	int	matched;
	int	expand;

	expand = 1;
	if (arg[0] == '\1')
	{
		expand = 0;
		ft_memmove(arg, arg + 1, ft_strlen(arg));
	}
	if (expand && ft_strchr(arg, '*'))
	{
		matched = match_dir_entries(arg, out);
		if (matched < 0)
			return (-1);
		if (matched == 0)
			return (store_word(out, arg));
		return (0);
	}
	return (store_word(out, arg));
}

char	**expand_wildcards(char **args)
{
	char			**out;
	int				i;

	out = NULL;
	i = 0;
	while (args && args[i])
	{
		if (add_entry(args[i], &out) < 0)
		{
			free_split(out);
			return (args);
		}
		i++;
	}
	if (out)
		return (out);
	return (args);
}
