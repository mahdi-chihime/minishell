/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:45:01 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 19:03:51 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*exec_get_cmd_node(t_node *node)
{
	while (node && node->type != N_CMD && node->type != N_SUBSHELL)
		node = node->left;
	return (node);
}

int	exec_save_std(int backup[2])
{
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	if (backup[0] < 0 || backup[1] < 0)
	{
		if (backup[0] >= 0)
			close(backup[0]);
		if (backup[1] >= 0)
			close(backup[1]);
		perror("dup");
		return (1);
	}
	return (0);
}

void	exec_restore_std(int backup[2])
{
	if (backup[0] >= 0)
	{
		dup2(backup[0], STDIN_FILENO);
		close(backup[0]);
	}
	if (backup[1] >= 0)
	{
		dup2(backup[1], STDOUT_FILENO);
		close(backup[1]);
	}
}

int	exec_apply_redirs_only(t_node *node, t_env *env, int last_status)
{
	int	backup[2];

	if (!node || node->type == N_CMD || node->type == N_SUBSHELL)
		return (0);
	if (exec_save_std(backup))
		return (1);
	if (handle_redirections(node, env, last_status))
	{
		exec_restore_std(backup);
		return (1);
	}
	exec_restore_std(backup);
	return (0);
}
