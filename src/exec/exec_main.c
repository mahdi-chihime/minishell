/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:47:12 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 22:20:46 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_node *node, t_env **env, char **args, int last_status)
{
	char	**envp;
	char	*path;
	int		err;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(node, *env, last_status))
		exit(1);
	err = resolve_cmd_path(args[0], *env, &envp, &path);
	if (err != 0)
		exit(err);
	execve(path, args, envp);
	perror(args[0]);
	free(path);
	free_split(envp);
	exit(127);
}

int	spawn_child(t_node *node, t_env **env, char **args, int last_status)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_child(node, env, args, last_status);
	set_ignore_signals();
	status = 0;
	waitpid(pid, &status, 0);
	set_shell_signals();
	return (wait_status_to_exit(status));
}

int	exec_cmd(t_node *node, t_env **env, int last_status)
{
	char	**args;
	t_node	*cmd;
	int		hd_status;

	hd_status = prepare_heredocs(node, *env, last_status);
	if (hd_status != 0)
		return (hd_status);
	cmd = exec_get_cmd_node(node);
	if (!cmd)
		return (0);
	if (cmd->type == N_SUBSHELL)
		return (exec_subshell(node, env, last_status));
	args = prepare_args(cmd);
	if (!args)
		return (0);
	if (!args[0])
		return (exec_apply_redirs_only(node, *env, last_status));
	if (is_builtin(args[0]))
		return (exec_run_builtin(node, env, cmd, last_status));
	return (spawn_child(node, env, args, last_status));
}

int	exec_tree(t_node *root, t_env **env, int last_status)
{
	int	status;

	if (!root)
		return (0);
	if (root->type == N_PIPE)
		return (exec_pipe(root, env, last_status));
	if (root->type == N_AND)
	{
		status = exec_tree(root->left, env, last_status);
		if (is_signal_status(status))
			return (status);
		if (status == 0)
			return (exec_tree(root->right, env, status));
		return (status);
	}
	if (root->type == N_OR)
	{
		status = exec_tree(root->left, env, last_status);
		if (is_signal_status(status))
			return (status);
		if (status != 0)
			return (exec_tree(root->right, env, status));
		return (status);
	}
	return (exec_cmd(root, env, last_status));
}
