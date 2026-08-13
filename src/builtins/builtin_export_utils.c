/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:27:24 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 11:29:07 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_nodes(t_env **nodes, int n)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(nodes[j]->key, nodes[j + 1]->key) > 0)
			{
				tmp = nodes[j];
				nodes[j] = nodes[j + 1];
				nodes[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static t_env	**env_nodes_sorted(t_env *env, int *n)
{
	t_env	**nodes;
	t_env	*cur;
	int		i;

	*n = 0;
	cur = env;
	while (cur)
	{
		(*n)++;
		cur = cur->next;
	}
	nodes = malloc(sizeof(t_env *) * (*n + 1));
	if (!nodes)
		return (NULL);
	i = 0;
	cur = env;
	while (cur)
	{
		nodes[i++] = cur;
		cur = cur->next;
	}
	nodes[i] = NULL;
	sort_nodes(nodes, *n);
	return (nodes);
}

static void	print_one_declare(t_env *node)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(node->key, STDOUT_FILENO);
	if (node->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(node->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	export_print(t_env *env)
{
	t_env	**nodes;
	int		n;
	int		i;

	nodes = env_nodes_sorted(env, &n);
	if (!nodes)
		return (1);
	i = 0;
	while (i < n)
	{
		print_one_declare(nodes[i]);
		i++;
	}
	free(nodes);
	return (0);
}
