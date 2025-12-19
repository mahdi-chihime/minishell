/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:19:49 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 19:52:56 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_to_str(t_token *tok)
{
	if (!tok)
		return ("newline");
	if (tok->type == T_PIPE)
		return ("|");
	if (tok->type == T_AND)
		return ("&&");
	if (tok->type == T_OR)
		return ("||");
	if (tok->type == T_REDIR_IN)
		return ("<");
	if (tok->type == T_REDIR_OUT)
		return (">");
	if (tok->type == T_REDIR_APPEND)
		return (">>");
	if (tok->type == T_HEREDOC)
		return ("<<");
	return ("?");
}

int	print_syntax_error(t_token *tok)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token_to_str(tok), 2);
	ft_putendl_fd("'", 2);
	return (1);
}

int	validate_tokens(t_token *tok)
{
	if (tok && (tok->type == T_PIPE || tok->type == T_AND || tok->type == T_OR))
		return (print_syntax_error(tok));
	while (tok)
	{
		if (is_redir_token(tok->type)
			&& (!tok->next || tok->next->type != T_WORD))
			return (print_syntax_error(tok->next));
		if ((tok->type == T_PIPE || tok->type == T_AND || tok->type == T_OR)
			&& (!tok->next || tok->next->type == T_PIPE
				|| tok->next->type == T_AND || tok->next->type == T_OR))
			return (print_syntax_error(tok->next));
		tok = tok->next;
	}
	return (0);
}

t_node	*parse_and_or(t_token **tok)
{
	t_node		*left;
	t_node_type	type;

	left = parse_pipeline(tok);
	if (!left)
		return (NULL);
	while (*tok && ((*tok)->type == T_AND || (*tok)->type == T_OR))
	{
		if ((*tok)->type == T_AND)
			type = N_AND;
		else
			type = N_OR;
		*tok = (*tok)->next;
		left = new_logic_node(left, type, tok);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_node	*parse_input(char *line, t_env *env, int last_status)
{
	t_token	*tokens;
	t_token	*head;
	t_node	*root;

	tokens = lexer(line, env, last_status);
	if (!tokens)
		return (NULL);
	if (validate_tokens(tokens))
		return (token_free(tokens), NULL);
	head = tokens;
	root = parse_and_or(&tokens);
	token_free(head);
	return (root);
}
