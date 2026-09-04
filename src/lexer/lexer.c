/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 21:42:39 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 18:48:27 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	return (i);
}

static t_token_type	single_op_type(char c)
{
	if (c == '|')
		return (T_PIPE);
	if (c == '<')
		return (T_IN);
	return (T_OUT);
}

int	lex_operator(t_token **tokens, const char *s)
{
	t_token_type	type;
	int				len;

	len = 1;
	if (s[0] == '<' && s[1] == '<')
	{
		type = T_HEREDOC;
		len = 2;
	}
	else if (s[0] == '>' && s[1] == '>')
	{
		type = T_APPEND;
		len = 2;
	}
	else
		type = single_op_type(s[0]);
	token_add(tokens, token_new(ft_substr(s, 0, len), type));
	return (len);
}

t_token	*lexer(const char *line, int *err)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		i += skip_spaces(line + i);
		if (!line[i])
			break ;
		if (is_operator_char(line[i]))
			i += lex_operator(&tokens, line + i);
		else
			i += lex_word(&tokens, line + i, err);
		if (*err)
		{
			token_free(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
