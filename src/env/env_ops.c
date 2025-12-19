/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:55:52 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/02 22:47:57 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

int	update_existing(t_env *cur, const char *val, int overwrite)
{
	if (!overwrite)
		return (0);
	free(cur->val);
	if (val)
	{
		cur->val = ft_strdup(val);
		if (!cur->val)
			return (1);
	}
	else
		cur->val = NULL;
	return (0);
}

int	env_set(t_env **env, const char *key, const char *val, int overwrite)
{
	t_env	*cur;
	t_env	*node;

	cur = *env;
	while (cur && ft_strcmp(cur->key, key))
		cur = cur->next;
	if (cur)
		return (update_existing(cur, val, overwrite));
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->key = ft_strdup(key);
	if (val)
		node->val = ft_strdup(val);
	if (!node->key || (val && !node->val))
	{
		free(node->key);
		free(node->val);
		free(node);
		return (1);
	}
	node->next = *env;
	*env = node;
	return (0);
}

int	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	prev = NULL;
	cur = *env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->val);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->val);
		free(env);
		env = tmp;
	}
}
