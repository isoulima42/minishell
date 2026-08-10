/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:36:52 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 10:55:22 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *name)
{
	if (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd"))
		return (1);
	if (!ft_strcmp(name, "pwd") || !ft_strcmp(name, "export"))
		return (1);
	if (!ft_strcmp(name, "unset") || !ft_strcmp(name, "env"))
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

int	run_builtin(t_shell *sh, t_cmd *cmd)
{
	char	*name;

	name = cmd->argv[0];
	if (!ft_strcmp(name, "echo"))
		return (builtin_echo(cmd));
	if (!ft_strcmp(name, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(name, "env"))
		return (builtin_env(sh));
	if (!ft_strcmp(name, "cd"))
		return (builtin_cd(sh, cmd));
	if (!ft_strcmp(name, "export"))
		return (builtin_export(sh, cmd));
	if (!ft_strcmp(name, "unset"))
		return (builtin_unset(sh, cmd));
	return (builtin_exit(sh, cmd));
}
