/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 16:11:15 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:12:07 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argv[0] = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	cmd_add_arg(t_cmd *cmd, char *arg)
{
	char	**new;
	int		n;
	int		i;

	n = 0;
	while (cmd->argv[n])
		n++;
	new = malloc(sizeof(char *) * (n + 2));
	if (!new)
		return (1);
	i = -1;
	while (++i < n)
		new[i] = cmd->argv[i];
	new[n] = ft_strdup(arg);
	new[n + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new;
	if (!new[n])
		return (1);
	return (0);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*cur;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->fd >= 0)
			close(redirs->fd);
		free(redirs->target);
		free(redirs);
		redirs = tmp;
	}
}

void	cmd_free(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_array(cmds->argv);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}
