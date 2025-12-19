/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:34:31 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/02 23:04:19 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type == T_WORD)
	{
		count++;
		tok = tok->next;
	}
	return (count);
}

char	*dup_value(t_token *tok)
{
	char	*copy;
	size_t	len;

	if (!tok->quoted)
		return (ft_strdup(tok->value));
	len = ft_strlen(tok->value);
	copy = malloc(len + 2);
	if (!copy)
		return (NULL);
	copy[0] = '\1';
	ft_strlcpy(copy + 1, tok->value, len + 1);
	return (copy);
}

int	add_quoted_arg(t_token *tok, char **args, int *i)
{
	args[*i] = dup_value(tok);
	if (!args[*i])
		return (1);
	(*i)++;
	return (0);
}

int	add_unquoted_args(t_token *tok, char **args, int *i)
{
	char	**parts;
	int		j;

	parts = ft_split(tok->value, ' ');
	if (!parts)
		return (1);
	j = 0;
	while (parts[j])
	{
		args[*i] = ft_strdup(parts[j]);
		if (!args[*i])
		{
			free_split(parts);
			return (1);
		}
		(*i)++;
		j++;
	}
	free_split(parts);
	return (0);
}

char	**collect_args(t_token **tok)
{
	char	**args;
	int		size;
	int		i;

	size = count_words(*tok) * 4 + 1;
	args = malloc(sizeof(char *) * size);
	if (!args)
		return (NULL);
	i = 0;
	while (*tok && (*tok)->type == T_WORD)
	{
		if ((*tok)->quoted)
		{
			if (add_quoted_arg(*tok, args, &i))
				return (free_split(args), NULL);
		}
		else if (add_unquoted_args(*tok, args, &i))
			return (free_split(args), NULL);
		*tok = (*tok)->next;
	}
	args[i] = NULL;
	return (args);
}
