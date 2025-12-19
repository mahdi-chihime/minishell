/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:03:21 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/02 14:06:30 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_last_status(int *i, int last)
{
	(*i)++;
	return (ft_itoa(last));
}

char	*expand_digit_var(char *s, int *i, t_env *env)
{
	char	*name;
	char	*val;

	if (ft_isdigit(s[*i]))
	{
		name = ft_substr(s, *i, 1);
		(*i)++;
		val = env_get(env, name);
		free(name);
		if (!val)
			return (ft_strdup(""));
		return (ft_strdup(val));
	}
	return (NULL);
}

char	*expand_named_var(char *s, int *i, t_env *env)
{
	int		start;
	char	*name;
	char	*val;

	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	if (start == *i)
	{
		if (s[*i] == '"' || s[*i] == '\'')
			return (ft_strdup(""));
		return (ft_strdup("$"));
	}
	name = ft_substr(s, start, *i - start);
	val = env_get(env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*expand_var(char *s, int *i, t_env *env, int last)
{
	char	*res;

	(*i)++;
	if (s[*i] == '?')
		return (expand_last_status(i, last));
	res = expand_digit_var(s, i, env);
	if (res)
		return (res);
	return (expand_named_var(s, i, env));
}

void	handle_dollar_in_dquote(t_expand *ex)
{
	char	*tmp;
	char	*add;

	tmp = ft_substr(ex->s, *(ex->start), *(ex->i) - *(ex->start));
	add = expand_var(ex->s, ex->i, ex->env, ex->last);
	*(ex->res) = ft_strjoin_free(*(ex->res), tmp);
	*(ex->res) = ft_strjoin_free(*(ex->res), add);
	*(ex->start) = *(ex->i);
}
