/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:26:49 by mchihime          #+#    #+#             */
/*   Updated: 2025/10/28 13:42:44 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(msg, 2);
}

void	exit_error(char *msg, int code)
{
	print_error(msg);
	exit(code);
}
