/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_from.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:55:10 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 19:50:52 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_skip_entry(char *entry, char *eq)
{
	return ((eq - entry) == 1 && entry[0] == '_');
}

t_env	*create_env_node(char *key, char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->val = val;
	node->next = NULL;
	return (node);
}

int	push_env_node(t_env **head, char *entry)
{
	char	*eq;
	char	*key;
	char	*val;
	t_env	*node;

	eq = ft_strchr(entry, '=');
	if (!eq || should_skip_entry(entry, eq))
		return (0);
	key = ft_substr(entry, 0, eq - entry);
	if (!key)
		return (-1);
	val = ft_strdup(eq + 1);
	if (!val)
		return (free(key), -1);
	node = create_env_node(key, val);
	if (!node)
	{
		free(key);
		free(val);
		return (-1);
	}
	node->next = *head;
	*head = node;
	return (0);
}

t_env	*env_from_environ(char **envp)
{
	t_env	*head;
	int		i;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (push_env_node(&head, envp[i]) < 0)
		{
			env_free(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}
