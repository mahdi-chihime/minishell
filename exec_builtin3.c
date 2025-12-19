/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bultin3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhaled <rakhaled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:29:23 by rakhaled          #+#    #+#             */
/*   Updated: 2025/12/12 20:30:03 by rakhaled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_unset(char **args, t_env **env)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			print_error("unset: not a valid identifier");
			err = 1;
		}
		else
			env_unset(env, args[i]);
		i++;
	}
	return (err);
}

int	bi_export(char **args, t_env **env)
{
	int	i;
	int	err;

	if (!args[1])
		return (print_export_sorted(*env));
	i = 1;
	err = 0;
	while (args[i])
	{
		if (export_one(args[i], env))
			err = 1;
		i++;
	}
	return (err);
}
