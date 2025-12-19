/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:25:35 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/04 00:48:14 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_tree(node->left);
	if (node->right)
		free_tree(node->right);
	free_split(node->cmd);
	free(node->file);
	free(node);
}
