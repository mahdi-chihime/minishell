/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:59:22 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 17:51:08 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_loop(char *s, t_token **list, t_env *env, int last_status)
{
	int				i;
	t_lexer_ctx		ctx;
	t_token_type	type;

	ctx.env = env;
	ctx.last_status = last_status;
	i = 0;
	while (s[i])
	{
		while (ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		if (is_op(s[i]))
		{
			type = get_op_type(s, &i);
			add_token(list, type, NULL, 0);
		}
		else
			handle_word(s, &i, list, ctx);
	}
}

t_token	*lexer(char *s, t_env *env, int last_status)
{
	t_token	*list;

	list = NULL;
	if (!s)
		return (NULL);
	lexer_loop(s, &list, env, last_status);
	return (list);
}
