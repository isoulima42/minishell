/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 17:13:31 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 11:07:15 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_shell *sh)
{
	char	*cwd;
	char	*old;

	old = env_get(sh->env, "PWD");
	if (old)
		env_set(&sh->env, "OLDPWD", old);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		env_set(&sh->env, "PWD", cwd);
		free(cwd);
	}
}

static char	*cd_target(t_shell *sh, t_cmd *cmd)
{
	if (!cmd->argv[1])
		return (env_get(sh->env, "HOME"));
	return (cmd->argv[1]);
}

int	builtin_cd(t_shell *sh, t_cmd *cmd)
{
	char	*target;

	if (cmd->argv[1] && cmd->argv[2])
	{
		print_error("cd", NULL, "too many arguments");
		return (1);
	}
	target = cd_target(sh, cmd);
	if (!target)
	{
		print_error("cd", NULL, "HOME not set");
		return (1);
	}
	if (chdir(target) != 0)
	{
		print_error("cd", target, strerror(errno));
		return (1);
	}
	update_pwd(sh);
	return (0);
}
