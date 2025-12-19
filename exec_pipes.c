/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:49:44 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 19:51:31 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_proc(t_node *right, t_env **env, int *fd, int last_status)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exit(exec_tree(right, env, last_status));
}

int	fork_children(t_pipe_ctx *ctx)
{
	ctx->pids[0] = fork();
	if (ctx->pids[0] < 0)
		return (perror("fork"), 1);
	if (ctx->pids[0] == 0)
		child_proc(ctx->node->left, ctx->env, ctx->fd, ctx->last_status);
	ctx->pids[1] = fork();
	if (ctx->pids[1] < 0)
		return (perror("fork"), 1);
	if (ctx->pids[1] == 0)
		parent_proc(ctx->node->right, ctx->env, ctx->fd, ctx->last_status);
	return (0);
}

int	prepare_pipe_heredocs(t_node *node, t_env **env, int last_status)
{
	int	status;

	status = prepare_heredocs(node->left, *env, last_status);
	if (status != 0)
		return (status);
	return (prepare_heredocs(node->right, *env, last_status));
}

int	wait_pipe_children(t_pipe_ctx *ctx, int status[2])
{
	int	exit_status;

	set_ignore_signals();
	waitpid(ctx->pids[1], &status[1], 0);
	exit_status = wait_status_to_exit(status[1]);
	waitpid(ctx->pids[0], &status[0], 0);
	set_shell_signals();
	return (exit_status);
}

int	exec_pipe(t_node *node, t_env **env, int last_status)
{
	t_pipe_ctx	ctx;
	int			status[2];

	ctx.node = node;
	ctx.env = env;
	ctx.last_status = last_status;
	ctx.fd[0] = 0;
	ctx.fd[1] = 0;
	ctx.pids[0] = 0;
	ctx.pids[1] = 0;
	status[0] = 0;
	status[1] = 0;
	status[0] = prepare_pipe_heredocs(node, env, last_status);
	if (status[0] != 0)
		return (status[0]);
	if (pipe(ctx.fd) == -1)
		return (perror("pipe"), 1);
	if (fork_children(&ctx))
		return (1);
	close(ctx.fd[0]);
	close(ctx.fd[1]);
	return (wait_pipe_children(&ctx, status));
}
