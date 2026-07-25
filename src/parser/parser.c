/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:14:44 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:04:44 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_token_to_cmd(t_cmd *cmd, t_token **tok)
{
	if ((*tok)->type == T_WORD)
	{
		if (cmd_add_arg(cmd, (*tok)->value))
			return (1);
		*tok = (*tok)->next;
		return (0);
	}
	return (parse_redir(cmd, tok));
}

static t_cmd	*build_cmd(t_token **tok, int *err)
{
	t_cmd	*cmd;

	cmd = cmd_new();
	if (!cmd)
	{
		*err = 1;
		return (NULL);
	}
	while (*tok && (*tok)->type != T_PIPE)
	{
		if (add_token_to_cmd(cmd, tok))
		{
			*err = 1;
			return (cmd);
		}
	}
	return (cmd);
}

t_cmd	*parser(t_token *tokens, int *err)
{
	t_cmd	*cmds;
	t_cmd	*cmd;

	cmds = NULL;
	while (tokens)
	{
		cmd = build_cmd(&tokens, err);
		if (*err)
		{
			cmd_free(cmds);
			cmd_free(cmd);
			return (NULL);
		}
		cmd_add_back(&cmds, cmd);
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (cmds);
}
