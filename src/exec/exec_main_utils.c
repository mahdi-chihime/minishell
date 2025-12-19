/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:00:00 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/11 22:49:47 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**prepare_args(t_node *cmd)
{
	char	**expanded;

	if (!cmd || !cmd->cmd)
		return (NULL);
	expanded = expand_wildcards(cmd->cmd);
	if (expanded && expanded != cmd->cmd)
	{
		free_split(cmd->cmd);
		cmd->cmd = expanded;
	}
	return (cmd->cmd);
}

int	validate_path(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
	{
		perror(path);
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		perror(path);
		return (126);
	}
	return (0);
}

int	cmd_not_found(char *cmd, char ***envp)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free_split(*envp);
	return (127);
}

int	resolve_cmd_path(char *cmd, t_env *env, char ***envp, char **path)
{
	int	err;

	*envp = env_to_environ(env);
	*path = find_in_path(cmd, env);
	if (!*path)
		return (cmd_not_found(cmd, envp));
	err = validate_path(*path);
	if (err != 0)
	{
		free(*path);
		free_split(*envp);
	}
	return (err);
}
