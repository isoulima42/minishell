/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:11:48 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 09:46:56 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = NULL;
	if (key)
		node = malloc(sizeof(t_env));
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **env, t_env *node)
{
	t_env	*cur;

	if (!*env)
	{
		*env = node;
		return ;
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

static int	env_add_pair(t_env **env, const char *str)
{
	char	*eq;
	t_env	*node;

	eq = ft_strchr(str, '=');
	if (!eq)
		node = env_new(ft_strdup(str), NULL);
	else
		node = env_new(ft_substr(str, 0, eq - str), ft_strdup(eq + 1));
	if (!node)
		return (1);
	env_add_back(env, node);
	return (0);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (env_add_pair(&env, envp[i]))
		{
			env_free(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
