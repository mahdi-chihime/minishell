/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_add_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:03:57 by rakhaled          #+#    #+#             */
/*   Updated: 2025/12/12 17:49:49 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(t_token_type type, char *value, int quoted)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->quoted = quoted;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **list, t_token_type type, char *val, int quoted)
{
	t_token	*new;
	t_token	*tmp;

	new = token_new(type, val, quoted);
	if (!new)
	{
		if (val)
			free(val);
		return ;
	}
	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
