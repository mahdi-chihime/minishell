/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:03:30 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/15 23:30:44 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_tilde(t_expand *ex)
{
	char	*tmp;
	char	*home;

	if (*(ex->i) != 0)
		return (0);
	if (ex->s[*(ex->i)] != '~')
		return (0);
	if (ex->s[*(ex->i) + 1] && ex->s[*(ex->i) + 1] != '/')
		return (0);
	home = getenv("HOME");
	if (!home)
		return (0);
	tmp = ft_substr(ex->s, *(ex->start), *(ex->i) - *(ex->start));
	*(ex->res) = ft_strjoin_free(*(ex->res), tmp);
	*(ex->res) = ft_strjoin_free(*(ex->res), ft_strdup(home));
	(*(ex->i))++;
	*(ex->start) = *(ex->i);
	return (1);
}

int	handle_escape(t_expand *ex, int *start)
{
	char	*tmp;

	if (ex->s[*(ex->i)] != '\\' || !ex->s[*(ex->i) + 1])
		return (0);
	tmp = ft_substr(ex->s, *start, *(ex->i) - *start);
	*(ex->res) = ft_strjoin_free(*(ex->res), tmp);
	*(ex->res) = ft_strjoin_free(*(ex->res), ft_substr(ex->s, *(ex->i) + 1, 1));
	*(ex->i) += 2;
	*start = *(ex->i);
	return (1);
}

void	process_segment(t_expand *ex)
{
	char	*tmp;
	char	*part;

	if (handle_escape(ex, ex->start))
		return ;
	if (handle_tilde(ex))
		return ;
	if (ex->s[*(ex->i)] == '\'' || ex->s[*(ex->i)] == '"'
		|| ex->s[*(ex->i)] == '$')
	{
		tmp = ft_substr(ex->s, *(ex->start), *(ex->i) - *(ex->start));
		if (ex->s[*(ex->i)] == '\'')
			part = expand_single_quote(ex->s, ex->i);
		else if (ex->s[*(ex->i)] == '"')
			part = expand_double_quotes(ex->s, ex->i, ex->env, ex->last);
		else
			part = expand_var(ex->s, ex->i, ex->env, ex->last);
		*(ex->res) = ft_strjoin_free(*(ex->res), tmp);
		*(ex->res) = ft_strjoin_free(*(ex->res), part);
		*(ex->start) = *(ex->i);
		return ;
	}
	(*(ex->i))++;
}

char	*expand_word(char *s, int *i, t_env *env, int last)
{
	char		*res;
	char		*tmp;
	int			start;
	t_expand	ex;

	res = ft_strdup("");
	start = *i;
	ex.s = s;
	ex.i = i;
	ex.env = env;
	ex.last = last;
	ex.res = &res;
	ex.start = &start;
	while (s[*i] && !ft_isspace(s[*i]) && !is_op(s[*i]))
		process_segment(&ex);
	tmp = ft_substr(s, start, *i - start);
	res = ft_strjoin_free(res, tmp);
	return (res);
}
