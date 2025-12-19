/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:59:06 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/10 20:58:04 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_result(t_here *ctx, int status, int keep, t_node *node)
{
	int	fd;

	if (status != 0)
	{
		close(ctx->fd);
		unlink(ctx->template);
		return (status);
	}
	close(ctx->fd);
	fd = open(ctx->template, O_RDONLY);
	if (fd < 0)
		return (unlink(ctx->template), 1);
	ctx->fd = fd;
	if (keep)
		return (set_keep_file(ctx, node));
	unlink(ctx->template);
	dup2(ctx->fd, STDIN_FILENO);
	close(ctx->fd);
	return (0);
}

int	write_line(t_here *ctx, char *line)
{
	char	*dup;
	char	*out;

	if (!ctx->node->hd_expand)
	{
		ft_putendl_fd(line, ctx->fd);
		return (0);
	}
	dup = ft_strdup(line);
	if (!dup)
		return (-1);
	out = expand_line_value(dup, ctx->env, ctx->last_status);
	if (!out)
		return (-1);
	ft_putendl_fd(out, ctx->fd);
	free(out);
	return (0);
}

int	read_loop(t_here *ctx)
{
	char	*line;
	int		status;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, ctx->node->file))
			return (free(line), 0);
		status = write_line(ctx, line);
		free(line);
		if (status < 0)
			return (1);
	}
	return (0);
}

int	init_heredoc_ctx(t_here *ctx, t_node *node, t_env *env, int last_status)
{
	static int	id = 0;
	char		*num;
	char		*tmp;

	ctx->node = node;
	ctx->env = env;
	ctx->last_status = last_status;
	id++;
	num = ft_itoa(id);
	if (!num)
		return (1);
	tmp = ft_strjoin("/tmp/minishell_hd_", num);
	free(num);
	if (!tmp)
		return (1);
	ft_strlcpy(ctx->template, tmp, sizeof(ctx->template));
	free(tmp);
	ctx->fd = open(ctx->template, O_CREAT | O_TRUNC | O_RDWR, 0600);
	if (ctx->fd < 0)
		return (perror("heredoc"), 1);
	return (0);
}

void	child_proc(t_node *left, t_env **env, int *fd, int last_status)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exit(exec_tree(left, env, last_status));
}
