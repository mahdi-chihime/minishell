/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:56:26 by mchihime          #+#    #+#             */
/*   Updated: 2025/11/25 18:39:06 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_length(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		if (env->val)
			len++;
		env = env->next;
	}
	return (len);
}

int	fill_output(char **out, t_env *env)
{
	int	index;

	index = 0;
	while (env)
	{
		if (env->val)
		{
			out[index] = ft_strjoin_three(env->key, "=", env->val);
			if (!out[index])
			{
				while (index > 0)
				{
					index--;
					free(out[index]);
				}
				return (-1);
			}
			index++;
		}
		env = env->next;
	}
	out[index] = NULL;
	return (0);
}

char	**env_to_environ(t_env *env)
{
	char	**out;
	int		len;

	len = env_length(env);
	out = malloc(sizeof(char *) * (len + 1));
	if (!out)
		return (NULL);
	if (fill_output(out, env) < 0)
	{
		free(out);
		return (NULL);
	}
	return (out);
}
