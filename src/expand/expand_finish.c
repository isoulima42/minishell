/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_finish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 21:54:26 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:53:30 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fields_to_array(t_list *fields)
{
	char	**arr;
	t_list	*tmp;
	int		i;

	arr = malloc(sizeof(char *) * (ft_lstsize(fields) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (fields)
	{
		arr[i] = (char *)fields->content;
		tmp = fields->next;
		free(fields);
		fields = tmp;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**expand_abort(t_expand *e)
{
	free(e->buf);
	ft_lstclear(&e->fields, free);
	return (NULL);
}

char	*expand_heredoc_line(t_shell *sh, const char *line)
{
	t_expand	e;
	int			i;

	init_expand(&e);
	if (!e.buf)
		return (NULL);
	e.quote = 2;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			i += expand_dollar(sh, &e, line + i);
		else if (append_char(&e, line[i]) == 0)
			i++;
		else
			break ;
	}
	ft_lstclear(&e.fields, free);
	return (e.buf);
}
