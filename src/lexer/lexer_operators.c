/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:02:07 by rakhaled          #+#    #+#             */
/*   Updated: 2025/12/12 17:48:20 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

t_token_type	get_op_type(char *s, int *i)
{
	if (s[*i] == '|' && s[*i + 1] == '|')
		return ((*i) += 2, T_OR);
	if (s[*i] == '&' && s[*i + 1] == '&')
		return ((*i) += 2, T_AND);
	if (s[*i] == '>' && s[*i + 1] == '>')
		return ((*i) += 2, T_REDIR_APPEND);
	if (s[*i] == '<' && s[*i + 1] == '<')
		return ((*i) += 2, T_HEREDOC);
	if (s[*i] == '|')
		return ((*i)++, T_PIPE);
	if (s[*i] == '>')
		return ((*i)++, T_REDIR_OUT);
	if (s[*i] == '<')
		return ((*i)++, T_REDIR_IN);
	if (s[*i] == '(')
		return ((*i)++, T_LPAREN);
	if (s[*i] == ')')
		return ((*i)++, T_RPAREN);
	return (T_WORD);
}
