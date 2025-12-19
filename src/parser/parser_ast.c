/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:24 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 17:37:00 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_pipe_node(t_node *left, t_token **tok)
{
	t_node	*right;
	t_node	*node;

	right = parse_factor(tok);
	if (!right)
	{
		free_tree(left);
		return (NULL);
	}
	node = new_node(N_PIPE, NULL);
	if (!node)
	{
		free_tree(right);
		free_tree(left);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*new_logic_node(t_node *left, t_node_type type, t_token **tok)
{
	t_node	*right;
	t_node	*node;

	right = parse_pipeline(tok);
	if (!right)
	{
		free_tree(left);
		return (NULL);
	}
	node = new_node(type, NULL);
	if (!node)
	{
		free_tree(right);
		free_tree(left);
		return (NULL);
	}
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*new_node(t_node_type type, char **cmd)
{
	t_node	*n;

	n = malloc(sizeof(t_node));
	if (!n)
		return (NULL);
	n->type = type;
	n->cmd = cmd;
	n->file = NULL;
	n->hd_expand = 1;
	n->hd_tmp = 0;
	n->left = NULL;
	n->right = NULL;
	return (n);
}
