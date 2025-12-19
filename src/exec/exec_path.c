/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:48:21 by mchihime          #+#    #+#             */
/*   Updated: 2025/11/25 18:39:48 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*full;

	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (!full)
			return (NULL);
		if (access(full, F_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*find_in_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_env;
	char	*full;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = env_get(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full = search_in_paths(paths, cmd);
	free_split(paths);
	return (full);
}
