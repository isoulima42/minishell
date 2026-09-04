/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 16:49:45 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 18:52:56 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *value, t_token_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
	{
		free(value);
		return (NULL);
	}
	tok->value = value;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

void	token_add(t_token **lst, t_token *new)
{
	t_token	*cur;

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

void	token_free(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_operator_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
