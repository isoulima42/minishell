/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 11:38:15 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 10:22:36 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_parent_builtin(t_cmd *cmd)
{
	if (!cmd->argv[0])
		return (0);
	return (is_builtin(cmd->argv[0]));
}

static int	run_parent_builtin(t_shell *sh, t_cmd *cmd)
{
	int	saved_in;
	int	saved_out;
	int	status;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redirs))
		status = 1;
	else
		status = run_builtin(sh, cmd);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	return (status);
}

int	execute(t_shell *sh)
{
	if (!sh->cmds->next && is_parent_builtin(sh->cmds))
		return (run_parent_builtin(sh, sh->cmds));
	return (run_pipeline(sh));
}
