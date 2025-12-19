/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:56:49 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 19:50:29 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_identifier_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	should_ignore_underscore(char *arg)
{
	if (!arg || arg[0] != '_')
		return (0);
	if (arg[1] == '\0')
		return (1);
	if (arg[1] == '=')
		return (1);
	return (0);
}

int	export_no_assign(char *arg, t_env **env)
{
	if (env_get(*env, arg))
		return (0);
	return (env_set(env, arg, NULL, 0));
}

int	export_with_assign(char *eq_pos, char *arg, t_env **env)
{
	char	*key;
	char	*val;
	int		ret;

	key = ft_substr(arg, 0, eq_pos - arg);
	val = ft_strdup(eq_pos + 1);
	if (!key || !val)
	{
		free(key);
		free(val);
		return (1);
	}
	ret = env_set(env, key, val, 1);
	free(key);
	free(val);
	return (ret != 0);
}

int	export_one(char *arg, t_env **env)
{
	char	*eq;

	if (should_ignore_underscore(arg))
		return (0);
	if (!is_valid_key(arg))
		return (export_identifier_error(arg));
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (export_no_assign(arg, env));
	return (export_with_assign(eq, arg, env));
}
