/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 11:54:51 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 11:13:56 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_shell(t_shell *sh, int code)
{
	shell_cleanup(sh);
	exit(code);
}

int	builtin_exit(t_shell *sh, t_cmd *cmd)
{
	int	code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->argv[1] && !is_numeric(cmd->argv[1]))
	{
		print_error("exit", cmd->argv[1], "numeric argument required");
		exit_shell(sh, 2);
	}
	if (cmd->argv[1] && cmd->argv[2])
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	code = sh->status;
	if (cmd->argv[1])
		code = ft_atoi(cmd->argv[1]);
	exit_shell(sh, (unsigned char)code);
	return (0);
}
