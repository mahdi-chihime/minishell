/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:21:15 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/15 23:31:01 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_dir(t_env *env)
{
	char	*home;

	home = env_get(env, "HOME");
	if (home && *home)
		return (home);
	return (NULL);
}
