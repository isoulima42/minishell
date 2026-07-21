/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 11:48:31 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 09:58:37 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_create(t_env **env, const char *key, char *value)
{
	t_env	*node;

	node = env_new(ft_strdup(key), value);
	if (!node)
		return (1);
	env_add_back(env, node);
	return (0);
}

int	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*node;
	char	*new_val;

	new_val = NULL;
	if (value)
	{
		new_val = ft_strdup(value);
		if (!new_val)
			return (1);
	}
	node = env_find(*env, key);
	if (node)
	{
		free(node->value);
		node->value = new_val;
		return (0);
	}
	return (env_create(env, key, new_val));
}

void	env_unset(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
