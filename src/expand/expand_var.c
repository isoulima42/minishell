/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 17:48:50 by anis              #+#    #+#             */
/*   Updated: 2026/09/03 19:36:59 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_name(const char *s)
{
	int	i;

	i = 0;
	if (s[0] == '_' || ft_isalpha(s[0]))
	{
		i = 1;
		while (s[i] == '_' || ft_isalnum(s[i]))
			i++;
	}
	return (i);
}

char	*var_value(t_shell *sh, const char *name)
{
	char	*v;

	if (!ft_strcmp(name, "?"))
		return (ft_itoa(sh->status));
	v = env_get(sh->env, name);
	if (!v)
		return (ft_strdup(""));
	return (ft_strdup(v));
}

int	append_value(t_expand *e, char *val)
{
	int	ret;

	if (!val)
		return (1);
	if (e->quote == 2)
		ret = append_str(e, val);
	else
		ret = append_split(e, val);
	free(val);
	return (ret);
}

static int	expand_brace(t_shell *sh, t_expand *e, const char *s)
{
	int		j;
	char	*name;

	j = 2;
	while (s[j] && s[j] != '}')
		j++;
	if (s[j] != '}')
	{
		append_char(e, '$');
		return (1);
	}
	name = ft_substr(s, 2, j - 2);
	if (name)
		append_value(e, var_value(sh, name));
	free(name);
	return (j + 1);
}

int	expand_dollar(t_shell *sh, t_expand *e, const char *s)
{
	int		len;
	char	*name;

	if (s[1] == '{')
		return (expand_brace(sh, e, s));
	if (s[1] == '?')
	{
		append_value(e, var_value(sh, "?"));
		return (2);
	}
	if (ft_isdigit(s[1]))
		return (2);
	len = read_name(s + 1);
	if (len == 0)
	{
		append_char(e, '$');
		return (1);
	}
	name = ft_substr(s, 1, len);
	if (name)
		append_value(e, var_value(sh, name));
	free(name);
	return (1 + len);
}
