/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:53:48 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/02 23:01:56 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(file), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_out(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(file), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_heredoc(t_node *node, t_env *env, int last_status)
{
	int	status;

	if (!node->hd_tmp)
		return (do_heredoc(node, env, 0, last_status));
	status = redir_in(node->file);
	unlink(node->file);
	free(node->file);
	node->file = NULL;
	node->hd_tmp = 0;
	return (status);
}

int	handle_redirections(t_node *node, t_env *env, int last_status)
{
	int	status;

	if (!node || node->type == N_CMD || node->type == N_SUBSHELL)
		return (0);
	if (node->left)
	{
		status = handle_redirections(node->left, env, last_status);
		if (status != 0)
			return (status);
	}
	if (node->type == N_REDIR_IN)
		return (redir_in(node->file));
	if (node->type == N_REDIR_OUT)
		return (redir_out(node->file, 0));
	if (node->type == N_REDIR_APPEND)
		return (redir_out(node->file, 1));
	if (node->type == N_HEREDOC)
		return (apply_heredoc(node, env, last_status));
	return (0);
}
