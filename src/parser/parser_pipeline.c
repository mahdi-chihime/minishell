/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:34:31 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 17:32:51 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_factor(t_token **tok)
{
	if (*tok && (*tok)->type == T_LPAREN)
		return (parse_subshell(tok));
	return (parse_command(tok));
}

t_node	*parse_pipeline(t_token **tok)
{
	t_node	*left;

	left = parse_factor(tok);
	if (!left)
		return (NULL);
	while (*tok && (*tok)->type == T_PIPE)
	{
		*tok = (*tok)->next;
		left = new_pipe_node(left, tok);
		if (!left)
			return (NULL);
	}
	return (left);
}
