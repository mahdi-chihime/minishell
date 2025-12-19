/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_runner.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:14:19 by mchihime          #+#    #+#             */
/*   Updated: 2025/11/26 20:22:56 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_node(t_node *node, t_env **env)
{
	if (!node || !node->cmd)
		return (0);
	if (!ft_strcmp(node->cmd[0], "echo"))
		return (bi_echo(node->cmd));
	if (!ft_strcmp(node->cmd[0], "cd"))
		return (bi_cd(node->cmd, env));
	if (!ft_strcmp(node->cmd[0], "pwd"))
		return (bi_pwd(*env));
	if (!ft_strcmp(node->cmd[0], "export"))
		return (bi_export(node->cmd, env));
	if (!ft_strcmp(node->cmd[0], "unset"))
		return (bi_unset(node->cmd, env));
	if (!ft_strcmp(node->cmd[0], "env"))
		return (bi_env(*env));
	if (!ft_strcmp(node->cmd[0], "exit"))
		return (bi_exit(node->cmd));
	return (0);
}
