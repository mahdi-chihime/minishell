/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:23:17 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 17:37:08 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type t)
{
	if (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_REDIR_APPEND
		|| t == T_HEREDOC)
		return (1);
	return (0);
}

t_node_type	get_redir_type(t_token_type t)
{
	if (t == T_REDIR_IN)
		return (N_REDIR_IN);
	if (t == T_REDIR_OUT)
		return (N_REDIR_OUT);
	if (t == T_REDIR_APPEND)
		return (N_REDIR_APPEND);
	return (N_HEREDOC);
}

t_node	*parse_redirs(t_token **tok, t_node *cmd)
{
	t_node		*redir;
	t_node_type	type;
	t_token		*file_tok;

	while (*tok && is_redir_token((*tok)->type))
	{
		type = get_redir_type((*tok)->type);
		file_tok = (*tok)->next;
		if (!file_tok || file_tok->type != T_WORD)
			break ;
		redir = malloc(sizeof(t_node));
		if (!redir)
			return (cmd);
		redir->type = type;
		redir->file = ft_strdup(file_tok->value);
		redir->cmd = NULL;
		redir->hd_expand = (type == N_HEREDOC && !file_tok->quoted);
		redir->hd_tmp = 0;
		redir->left = cmd;
		redir->right = NULL;
		cmd = redir;
		*tok = file_tok->next;
	}
	return (cmd);
}
