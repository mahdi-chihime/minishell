/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:28:59 by rakhaled          #+#    #+#             */
/*   Updated: 2025/12/12 20:26:22 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_command(t_token **tok)
{
	t_node	*root;
	t_node	*cmd;
	char	**extra;
	char	**args;

	args = collect_args(tok);
	if (!args)
		return (NULL);
	cmd = new_node(N_CMD, args);
	if (!cmd)
		return (free_split(args), NULL);
	root = cmd;
	while (*tok && ((*tok)->type == T_WORD || is_redir_token((*tok)->type)))
	{
		root = parse_redirs(tok, root);
		if (!*tok || (*tok)->type != T_WORD)
			break ;
		extra = collect_args(tok);
		if (!extra || append_args(&cmd->cmd, extra))
			return (free_tree(root), NULL);
	}
	return (root);
}
