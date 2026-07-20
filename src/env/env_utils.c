/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:14:18 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 09:51:55 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_find(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*env_get(t_env *env, const char *key)
{
	t_env	*node;

	node = env_find(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}

static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->value)
			n++;
		env = env->next;
	}
	return (n);
}

static int	fill_array(char **arr, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
		{
			arr[i] = ft_strjoin3(env->key, "=", env->value);
			if (!arr[i])
				return (1);
			i++;
		}
		env = env->next;
	}
	arr[i] = NULL;
	return (0);
}

char	**env_to_array(t_env *env)
{
	char	**arr;

	arr = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!arr)
		return (NULL);
	if (fill_array(arr, env))
	{
		free_array(arr);
		return (NULL);
	}
	return (arr);
}
