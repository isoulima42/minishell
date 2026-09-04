/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:38:28 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:21:17 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	redir_type(t_token_type t)
{
	if (t == T_IN)
		return (R_IN);
	if (t == T_APPEND)
		return (R_APPEND);
	if (t == T_HEREDOC)
		return (R_HEREDOC);
	return (R_OUT);
}

static char	*strip_delim(const char *raw, int *expand)
{
	char	*out;
	int		i;
	int		j;
	char	quote;

	out = malloc(ft_strlen(raw) + 1);
	if (!out)
		return (NULL);
	i = -1;
	j = 0;
	quote = 0;
	while (raw[++i])
	{
		if (!quote && (raw[i] == '\'' || raw[i] == '"'))
		{
			quote = raw[i];
			*expand = 0;
		}
		else if (quote && raw[i] == quote)
			quote = 0;
		else
			out[j++] = raw[i];
	}
	out[j] = '\0';
	return (out);
}

static t_redir	*make_redir(t_redir_type type, char *raw)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->expand = 1;
	redir->fd = -1;
	redir->next = NULL;
	if (type == R_HEREDOC)
		redir->target = strip_delim(raw, &redir->expand);
	else
		redir->target = ft_strdup(raw);
	if (!redir->target)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

static void	redir_add(t_redir **lst, t_redir *new)
{
	t_redir	*cur;

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

int	parse_redir(t_cmd *cmd, t_token **tok)
{
	t_redir	*redir;
	t_token	*target;

	target = (*tok)->next;
	if (!target || target->type != T_WORD)
		return (1);
	redir = make_redir(redir_type((*tok)->type), target->value);
	if (!redir)
		return (1);
	redir_add(&cmd->redirs, redir);
	*tok = target->next;
	return (0);
}
