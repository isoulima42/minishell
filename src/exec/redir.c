/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 13:16:32 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 10:42:35 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redir(t_redir *r)
{
	int	fd;

	if (r->type == R_IN)
		fd = open(r->target, O_RDONLY);
	else if (r->type == R_APPEND)
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_error(r->target, NULL, strerror(errno));
	return (fd);
}

static int	apply_file_redir(t_redir *r)
{
	int	fd;

	fd = open_redir(r);
	if (fd < 0)
		return (1);
	if (r->type == R_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	apply_heredoc(t_redir *r)
{
	if (r->fd < 0)
		return (1);
	if (dup2(r->fd, STDIN_FILENO) == -1)
		return (1);
	return (0);
}

int	apply_redirs(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == R_HEREDOC)
		{
			if (apply_heredoc(redirs))
				return (1);
		}
		else if (apply_file_redir(redirs))
			return (1);
		redirs = redirs->next;
	}
	return (0);
}
