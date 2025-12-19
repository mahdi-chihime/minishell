/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:49:11 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/12 13:03:43 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	bi_exit(char **args)
{
	long	code;

	ft_putendl_fd("exit", 1);
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		print_error("exit: numeric argument required");
		exit(2);
	}
	if (args[2])
	{
		print_error("exit: too many arguments");
		return (1);
	}
	code = (long)ft_atoi(args[1]);
	exit((unsigned char)code);
}

char	*join_path_fallback(char *pwd, char *path)
{
	char	*base;
	char	*res;

	if (!path || !*path)
	{
		if (pwd)
			return (ft_strdup(pwd));
		return (NULL);
	}
	if (!pwd || !*pwd || path[0] == '/')
		return (ft_strdup(path));
	base = ft_strjoin(pwd, "/");
	if (!base)
		return (NULL);
	res = ft_strjoin(base, path);
	free(base);
	return (res);
}

void	init_oldpwd(char oldpwd[4096], t_env *env)
{
	char	*tmp;

	if (getcwd(oldpwd, 4096))
		return ;
	tmp = env_get(env, "PWD");
	if (tmp)
		ft_strlcpy(oldpwd, tmp, 4096);
	else
		oldpwd[0] = '\0';
}
