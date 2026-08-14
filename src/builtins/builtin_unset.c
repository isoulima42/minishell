/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 12:02:31 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 11:38:14 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_shell *sh, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (is_valid_identifier(cmd->argv[i])
			&& !ft_strchr(cmd->argv[i], '='))
			env_unset(&sh->env, cmd->argv[i]);
		i++;
	}
	return (0);
}
