/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 19:01:08 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:45:25 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_expand(t_expand *e)
{
	e->buf = ft_strdup("");
	e->fields = NULL;
	e->started = 0;
	e->quote = 0;
}

int	append_str(t_expand *e, const char *s)
{
	char	*joined;

	joined = ft_strjoin(e->buf, s);
	if (!joined)
		return (1);
	free(e->buf);
	e->buf = joined;
	e->started = 1;
	return (0);
}

int	append_char(t_expand *e, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_str(e, str));
}

void	finalize_field(t_expand *e)
{
	t_list	*node;

	if (!e->started)
		return ;
	node = ft_lstnew(ft_strdup(e->buf));
	if (node)
		ft_lstadd_back(&e->fields, node);
	free(e->buf);
	e->buf = ft_strdup("");
	e->started = 0;
}

int	append_split(t_expand *e, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_space(s[i]))
			finalize_field(e);
		else if (append_char(e, s[i]))
			return (1);
		i++;
	}
	return (0);
}
