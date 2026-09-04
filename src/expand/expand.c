/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 18:03:42 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:33:32 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_fields(t_cmd *cmd, char **fields)
{
	int	k;

	k = 0;
	while (fields[k])
	{
		if (cmd_add_arg(cmd, fields[k]))
		{
			free_array(fields);
			return (1);
		}
		k++;
	}
	free_array(fields);
	return (0);
}

static int	rebuild_argv(t_shell *sh, t_cmd *cmd)
{
	char	**old;
	char	**fields;
	int		i;

	old = cmd->argv;
	cmd->argv = malloc(sizeof(char *));
	if (!cmd->argv)
		return (1);
	cmd->argv[0] = NULL;
	i = -1;
	while (old[++i])
	{
		fields = expand_word(sh, old[i]);
		if (!fields || append_fields(cmd, fields))
		{
			free_array(old);
			return (1);
		}
	}
	free_array(old);
	return (0);
}

static int	set_redir_target(t_redir *r, char **fields)
{
	if (!fields[0] || fields[1])
	{
		print_error(fields[0], NULL, "ambiguous redirect");
		free_array(fields);
		return (1);
	}
	free(r->target);
	r->target = fields[0];
	free(fields);
	return (0);
}

static int	expand_redirs_list(t_shell *sh, t_cmd *cmd)
{
	t_redir	*r;
	char	**fields;

	r = cmd->redirs;
	while (r)
	{
		if (r->type != R_HEREDOC)
		{
			fields = expand_word(sh, r->target);
			if (!fields || set_redir_target(r, fields))
				return (1);
		}
		r = r->next;
	}
	return (0);
}

int	expand_cmds(t_shell *sh, t_cmd *cmds)
{
	while (cmds)
	{
		if (rebuild_argv(sh, cmds))
			return (1);
		if (expand_redirs_list(sh, cmds))
			return (1);
		cmds = cmds->next;
	}
	return (0);
}
