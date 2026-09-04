/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 20:24:35 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 18:58:14 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_len(const char *s, int *unclosed)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (quote && s[i] == quote)
			quote = 0;
		else if (!quote && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (!quote && (is_space(s[i]) || is_operator_char(s[i])))
			break ;
		i++;
	}
	*unclosed = (quote != 0);
	return (i);
}

int	lex_word(t_token **tokens, const char *s, int *err)
{
	int	len;
	int	unclosed;

	len = word_len(s, &unclosed);
	if (unclosed)
	{
		print_error(NULL, NULL, "syntax error: unclosed quote");
		*err = 1;
		return (0);
	}
	token_add(tokens, token_new(ft_substr(s, 0, len), T_WORD));
	return (len);
}
