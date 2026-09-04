/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 19:28:58 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:26:43 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_token_type t)
{
	if (t == T_IN || t == T_OUT || t == T_APPEND || t == T_HEREDOC)
		return (1);
	return (0);
}

static int	syntax_error(char *sym)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(sym, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

static char	*next_symbol(t_token *tok)
{
	if (!tok)
		return ("newline");
	return (tok->value);
}

int	syntax_check(t_token *tokens)
{
	if (tokens && tokens->type == T_PIPE)
		return (syntax_error("|"));
	while (tokens)
	{
		if (is_redir(tokens->type))
		{
			if (!tokens->next || tokens->next->type != T_WORD)
				return (syntax_error(next_symbol(tokens->next)));
		}
		else if (tokens->type == T_PIPE)
		{
			if (!tokens->next || tokens->next->type == T_PIPE)
				return (syntax_error(next_symbol(tokens->next)));
		}
		tokens = tokens->next;
	}
	return (0);
}
