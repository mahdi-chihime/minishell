/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:20:27 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/15 15:42:27 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remember_dirs(t_env **env, char *oldpwd)
{
	char	cwd[4096];

	if (oldpwd)
		env_set(env, "OLDPWD", oldpwd, 1);
	else
		env_set(env, "OLDPWD", "", 1);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(env, "PWD", cwd, 1);
}

int	switch_to_oldpwd(t_env **env, char *oldpwd)
{
	char	*target;

	target = env_get(*env, "OLDPWD");
	if (!target)
		return (print_error("cd: OLDPWD not set"), 1);
	if (chdir(target) != 0)
		return (perror("cd"), 1);
	remember_dirs(env, oldpwd);
	target = env_get(*env, "PWD");
	if (target)
		ft_putendl_fd(target, 1);
	return (0);
}

char	*pick_target(char **args, t_env **env)
{
	char	*home;

	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--"))
	{
		home = get_home_dir(*env);
		if (!home || !*home)
			return (print_error("cd: HOME not set"), NULL);
		return (home);
	}
	return (args[1]);
}

int	update_pwd(t_env **env, char oldpwd[4096], char *path)
{
	char	cwd[4096];
	char	*pwd_fallback;

	if (getcwd(cwd, sizeof(cwd)))
	{
		env_set(env, "OLDPWD", oldpwd, 1);
		env_set(env, "PWD", cwd, 1);
		return (0);
	}
	pwd_fallback = join_path_fallback(env_get(*env, "PWD"), path);
	env_set(env, "OLDPWD", oldpwd, 1);
	if (pwd_fallback)
	{
		env_set(env, "PWD", pwd_fallback, 1);
		free(pwd_fallback);
	}
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putendl_fd("getcwd: cannot access parent directories", 2);
	return (0);
}

int	bi_cd(char **args, t_env **env)
{
	char	oldpwd[4096];
	char	*path;

	if (args[1] && args[2])
		return (print_error("cd: too many arguments"), 1);
	init_oldpwd(oldpwd, *env);
	if (args[1] && !ft_strcmp(args[1], "-"))
		return (switch_to_oldpwd(env, oldpwd));
	path = pick_target(args, env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	return (update_pwd(env, oldpwd, path));
}
