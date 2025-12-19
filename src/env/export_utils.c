/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 22:30:00 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/02 23:01:43 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_env_array(t_env *env, t_env ***arr, int *len)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	*len = i;
	if (i == 0)
		return (0);
	*arr = malloc(sizeof(t_env *) * i);
	if (!*arr)
		return (1);
	tmp = env;
	i = 0;
	while (tmp)
	{
		(*arr)[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	return (0);
}

void	sort_env_array(t_env **arr, int len)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_entry(t_env *item)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(item->key, 1);
	if (item->val)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(item->val, 1);
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putchar_fd('\n', 1);
}

int	print_export_sorted(t_env *env)
{
	t_env	**arr;
	int		len;
	int		i;

	if (fill_env_array(env, &arr, &len))
		return (1);
	if (len == 0)
		return (0);
	sort_env_array(arr, len);
	i = 0;
	while (i < len)
		print_export_entry(arr[i++]);
	free(arr);
	return (0);
}
