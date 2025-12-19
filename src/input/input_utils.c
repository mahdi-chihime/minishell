/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:17:28 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 00:33:25 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quote(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '"' || line[i] == '\''))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

char	*read_more_line(char *line)
{
	char	*more;
	char	*joined;

	more = readline("> ");
	if (!more)
	{
		free(line);
		return (NULL);
	}
	if (g_sig)
	{
		free(line);
		free(more);
		return (NULL);
	}
	joined = ft_strjoin_three(line, "\n", more);
	free(line);
	free(more);
	return (joined);
}

char	*read_full_line(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (g_sig && (!line || !*line))
	{
		free(line);
		return (NULL);
	}
	while (line && has_unclosed_quote(line))
	{
		line = read_more_line(line);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*expand_line_value(char *s, t_env *env, int last)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (free(s), NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			tmp = expand_var(s, &i, env, last);
			res = ft_strjoin_free(res, tmp);
			continue ;
		}
		tmp = ft_substr(s, i, 1);
		res = ft_strjoin_free(res, tmp);
		i++;
	}
	free(s);
	return (res);
}

int	set_keep_file(t_here *ctx, t_node *node)
{
	free(node->file);
	node->file = ft_strdup(ctx->template);
	if (!node->file)
		return (close(ctx->fd), unlink(ctx->template), 1);
	node->hd_tmp = 1;
	return (0);
}
