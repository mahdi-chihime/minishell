/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:05:58 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 20:27:18 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_inside_dquotes(t_expand *ex)
{
	while (ex->s[*(ex->i)] && ex->s[*(ex->i)] != '"')
	{
		if (ex->s[*(ex->i)] == '$')
			handle_dollar_in_dquote(ex);
		else
			(*(ex->i))++;
	}
}

char	*expand_double_quotes(char *s, int *i, t_env *env, int last)
{
	char		*res;
	char		*tmp;
	int			start;
	t_expand	ex;

	res = ft_strdup("");
	(*i)++;
	start = *i;
	ex.s = s;
	ex.i = i;
	ex.env = env;
	ex.last = last;
	ex.res = &res;
	ex.start = &start;
	handle_inside_dquotes(&ex);
	tmp = ft_substr(s, start, *i - start);
	res = ft_strjoin_free(res, tmp);
	if (s[*i] == '"')
		(*i)++;
	return (res);
}

char	*expand_single_quote(char *s, int *i)
{
	int		start;
	char	*res;

	start = ++(*i);
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	res = ft_substr(s, start, *i - start);
	if (s[*i])
		(*i)++;
	return (res);
}

char	*expand_token_value(char *s, t_env *env, int last)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	res = expand_word(s, &i, env, last);
	free(s);
	return (res);
}
