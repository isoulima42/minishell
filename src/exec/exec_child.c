/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 12:31:18 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 10:38:59 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_error_code(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error(path, NULL, "Is a directory");
		return (126);
	}
	print_error(path, NULL, strerror(errno));
	if (errno == EACCES)
		return (126);
	return (127);
}

static int	run_external(t_shell *sh, t_cmd *cmd)
{
	char	*path;
	char	**envp;
	int		code;

	path = resolve_path(sh->env, cmd->argv[0]);
	if (!path)
	{
		print_error(cmd->argv[0], NULL, "command not found");
		return (127);
	}
	envp = env_to_array(sh->env);
	execve(path, cmd->argv, envp);
	code = exec_error_code(path);
	free(path);
	free_array(envp);
	return (code);
}

int	exec_child(t_shell *sh, t_cmd *cmd)
{
	if (apply_redirs(cmd->redirs))
		return (1);
	if (!cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv[0]))
		return (run_builtin(sh, cmd));
	return (run_external(sh, cmd));
}
