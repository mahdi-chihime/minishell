/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:51:11 by rakhaled          #+#    #+#             */
/*   Updated: 2025/12/15 14:55:46 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_quote(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (1);
		s++;
	}
	return (0);
}

char	*read_word(char *s, int *i)
{
	int		start;
	char	quote;
	char	*res;

	start = *i;
	while (s[*i] && !is_op(s[*i]) && !ft_isspace(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			quote = s[*i];
			(*i)++;
			while (s[*i] && s[*i] != quote)
				(*i)++;
			if (s[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	res = ft_substr(s, start, *i - start);
	return (res);
}

void	handle_word(char *s, int *i, t_token **list, t_lexer_ctx ctx)
{
	char	*raw;
	char	*expanded;
	int		quoted;

	raw = read_word(s, i);
	if (!raw)
		return ;
	quoted = contains_quote(raw);
	expanded = expand_token_value(raw, ctx.env, ctx.last_status);
	add_token(list, T_WORD, expanded, quoted);
}
