/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:34:47 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 11:19:41 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_id_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static void	declare_var(t_shell *sh, char *key)
{
	if (!env_find(sh->env, key))
		env_set(&sh->env, key, NULL);
}

static int	export_one(t_shell *sh, char *arg)
{
	char	*eq;
	char	*key;
	int		ret;

	if (!is_valid_identifier(arg))
	{
		export_id_error(arg);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		declare_var(sh, arg);
		return (0);
	}
	key = ft_substr(arg, 0, eq - arg);
	ret = env_set(&sh->env, key, eq + 1);
	free(key);
	return (ret);
}

int	builtin_export(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	status;

	if (!cmd->argv[1])
		return (export_print(sh->env));
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (export_one(sh, cmd->argv[i]))
			status = 1;
		i++;
	}
	return (status);
}
