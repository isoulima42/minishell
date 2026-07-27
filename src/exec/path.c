/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 11:54:06 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 10:17:02 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_dirs(char **dirs, const char *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full = ft_strjoin3(dirs[i], "/", cmd);
		if (full && access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*resolve_path(t_env *env, const char *cmd)
{
	char	**dirs;
	char	*path;
	char	*pathenv;

	if (!cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	pathenv = env_get(env, "PATH");
	if (!pathenv || !pathenv[0])
		return (NULL);
	dirs = ft_split(pathenv, ':');
	if (!dirs)
		return (NULL);
	path = search_dirs(dirs, cmd);
	free_array(dirs);
	return (path);
}
