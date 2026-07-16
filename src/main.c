/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:41:26 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 12:04:15 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	init_shell(t_shell *sh, char **envp)
{
	sh->env = env_init(envp);
	sh->cmds = NULL;
	sh->status = 0;
}

void	shell_cleanup(t_shell *sh)
{
	env_free(sh->env);
	cmd_free(sh->cmds);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;
	int		status;

	(void)argv;
	if (argc != 1)
		return (1);
	init_shell(&sh, envp);
	shell_loop(&sh);
	status = sh.status;
	shell_cleanup(&sh);
	return (status);
}
