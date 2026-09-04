/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 15:53:38 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:42:11 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_closing_quote(t_expand *e, char c)
{
	if (e->quote == 1 && c == '\'')
		return (1);
	if (e->quote == 2 && c == '"')
		return (1);
	return (0);
}

static void	handle_quote(t_expand *e, char c)
{
	if (c == '\'')
		e->quote = 1;
	else
		e->quote = 2;
	e->started = 1;
}

int	run_expand(t_shell *sh, t_expand *e, const char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (e->quote == 0 && (word[i] == '\'' || word[i] == '"'))
			handle_quote(e, word[i]);
		else if (is_closing_quote(e, word[i]))
			e->quote = 0;
		else if (word[i] == '$' && e->quote != 1)
			i += expand_dollar(sh, e, word + i) - 1;
		else if (append_char(e, word[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**expand_word(t_shell *sh, const char *word)
{
	t_expand	e;

	init_expand(&e);
	if (!e.buf)
		return (NULL);
	if (run_expand(sh, &e, word))
		return (expand_abort(&e));
	finalize_field(&e);
	free(e.buf);
	return (fields_to_array(e.fields));
}
