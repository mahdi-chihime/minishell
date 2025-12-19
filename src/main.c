/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 13:28:37 by mchihime          #+#    #+#             */
/*   Updated: 2025/12/16 19:52:22 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_loop(char *line, t_node *root)
{
	if (line)
		free(line);
	if (root)
		free_tree(root);
}

int	handle_interrupted_read(char *line, int *last_status)
{
	if (!g_sig)
		return (0);
	g_sig = 0;
	*last_status = 130;
	if (!line || *line == '\0')
		return (free(line), 1);
	return (0);
}

void	set_shlvl(t_env **env)
{
	char	*val;
	int		n;
	char	*num;

	val = env_get(*env, "SHLVL");
	if (!val)
	{
		env_set(env, "SHLVL", "1", 1);
		return ;
	}
	n = ft_atoi(val) + 1;
	if (n < 0)
		n = 0;
	num = ft_itoa(n);
	if (!num)
		return ;
	env_set(env, "SHLVL", num, 1);
	free(num);
}

void	shell_loop(t_env **env)
{
	char	*line;
	t_node	*root;
	int		last_status;

	last_status = 0;
	while (1)
	{
		line = read_full_line();
		if (handle_interrupted_read(line, &last_status))
			continue ;
		if (!line)
			break ;
		if (*line)
			add_history(line);
		root = parse_input(line, *env, last_status);
		if (root)
			last_status = exec_tree(root, env, last_status);
		free_loop(line, root);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = env_from_environ(envp);
	if (!env)
		return (1);
	set_shlvl(&env);
	set_shell_signals();
	shell_loop(&env);
	env_free(env);
	printf("exit\n");
	return (0);
}
