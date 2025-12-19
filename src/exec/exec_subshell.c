/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:34:31 by mchihime          #+#    #+#             */
/*   Updated: 2025/11/05 13:34:31 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_subshell(t_node *node, t_env **env, int last_status)
{
	pid_t	pid;
	int		status;
	t_node	*sub;

	sub = exec_get_cmd_node(node);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (handle_redirections(node, *env, last_status))
			exit(1);
		if (sub && sub->left)
			exit(exec_tree(sub->left, env, last_status));
		exit(0);
	}
	set_ignore_signals();
	status = 0;
	waitpid(pid, &status, 0);
	set_shell_signals();
	return (wait_status_to_exit(status));
}
