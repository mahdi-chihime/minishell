/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:52:44 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/11 21:30:03 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

int	launch_heredoc_child(t_here *ctx, pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
		return (perror("fork"), close(ctx->fd), unlink(ctx->template), 1);
	if (*pid == 0)
	{
		signal(SIGINT, heredoc_sigint);
		signal(SIGQUIT, SIG_IGN);
		exit(read_loop(ctx));
	}
	return (0);
}

int	wait_heredoc(pid_t pid, t_here *ctx, int keep, t_node *node)
{
	int	status;

	set_ignore_signals();
	waitpid(pid, &status, 0);
	set_shell_signals();
	if (WIFSIGNALED(status))
		return (close(ctx->fd), unlink(ctx->template), 130);
	status = WEXITSTATUS(status);
	if (status == 130)
		return (close(ctx->fd), unlink(ctx->template), 130);
	if (status != 0)
		return (close_result(ctx, status, 0, node));
	return (close_result(ctx, 0, keep, node));
}

int	do_heredoc(t_node *node, t_env *env, int prepare_only, int last_status)
{
	t_here	ctx;
	pid_t	pid;

	if (init_heredoc_ctx(&ctx, node, env, last_status))
		return (1);
	if (launch_heredoc_child(&ctx, &pid))
		return (1);
	return (wait_heredoc(pid, &ctx, prepare_only, node));
}

int	prepare_heredocs(t_node *node, t_env *env, int last_status)
{
	int	status;

	if (!node)
		return (0);
	if (node->left)
	{
		status = prepare_heredocs(node->left, env, last_status);
		if (status != 0)
			return (status);
	}
	if (node->type == N_HEREDOC && !node->hd_tmp)
	{
		status = do_heredoc(node, env, 1, last_status);
		if (status != 0)
			return (status);
	}
	if (node->right)
	{
		status = prepare_heredocs(node->right, env, last_status);
		if (status != 0)
			return (status);
	}
	return (0);
}
