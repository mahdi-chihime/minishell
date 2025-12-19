/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:56:30 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 14:33:16 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *s)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	len = i;
	if (len == 1 && *s == '_')
		return (0);
	return (1);
}

int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	bi_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (args[i] && is_n_flag(args[i]))
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	bi_pwd(t_env *env)
{
	char	*pwd;
	char	cwd[4096];

	pwd = env_get(env, "PWD");
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

int	bi_env(t_env *env)
{
	while (env)
	{
		if (env->key && env->val)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->val, 1);
		}
		env = env->next;
	}
	return (0);
}
