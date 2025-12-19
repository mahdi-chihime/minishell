/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:32:54 by rakhaled          #+#    #+#             */
/*   Updated: 2025/12/12 20:28:13 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_subshell(t_token **tok)
{
	t_node	*inside;
	t_node	*sub;

	if (!tok || !*tok || (*tok)->type != T_LPAREN)
		return (NULL);
	*tok = (*tok)->next;
	inside = parse_and_or(tok);
	if (!inside)
		return (NULL);
	if (!*tok || (*tok)->type != T_RPAREN)
	{
		free_tree(inside);
		return (NULL);
	}
	*tok = (*tok)->next;
	sub = new_node(N_SUBSHELL, NULL);
	if (!sub)
	{
		free_tree(inside);
		return (NULL);
	}
	sub->left = inside;
	return (parse_redirs(tok, sub));
}

void	token_free(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = tmp;
	}
}
