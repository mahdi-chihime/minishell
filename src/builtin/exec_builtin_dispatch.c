/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_dispatch.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:45:58 by mchihime          #+#    #+#             */
/*   Updated: 2025/11/02 16:45:58 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *s)
{
	if (!s)
		return (0);
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd")
		|| !ft_strcmp(s, "pwd") || !ft_strcmp(s, "export")
		|| !ft_strcmp(s, "unset") || !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

int	exec_run_builtin(t_node *node, t_env **env, t_node *cmd, int last_status)
{
	int	backup[2];
	int	ret;

	if (!node || node->type == N_CMD)
		return (exec_builtin_node(cmd, env));
	if (exec_save_std(backup))
		return (1);
	if (handle_redirections(node, *env, last_status))
	{
		exec_restore_std(backup);
		return (1);
	}
	ret = exec_builtin_node(cmd, env);
	exec_restore_std(backup);
	return (ret);
}
