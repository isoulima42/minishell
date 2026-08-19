/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 12:09:07 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 11:46:10 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	close(STDIN_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}

void	set_signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

static void	heredoc_line_out(t_shell *sh, int fd, char *line, int expand)
{
	char	*out;

	if (expand)
	{
		out = expand_heredoc_line(sh, line);
		if (out)
		{
			ft_putstr_fd(out, fd);
			free(out);
		}
	}
	else
		ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

static int	read_one_heredoc(t_shell *sh, t_redir *r)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (1);
	line = readline("> ");
	while (line && ft_strcmp(line, r->target) != 0 && g_signal != SIGINT)
	{
		heredoc_line_out(sh, pipefd[1], line, r->expand);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(pipefd[1]);
	r->fd = pipefd[0];
	return (g_signal == SIGINT);
}

int	collect_heredocs(t_shell *sh, t_cmd *cmds)
{
	t_redir	*r;
	int		backup;
	int		aborted;

	backup = dup(STDIN_FILENO);
	set_signals_heredoc();
	aborted = 0;
	while (cmds && !aborted)
	{
		r = cmds->redirs;
		while (r && !aborted)
		{
			if (r->type == R_HEREDOC && read_one_heredoc(sh, r))
				aborted = 1;
			r = r->next;
		}
		cmds = cmds->next;
	}
	dup2(backup, STDIN_FILENO);
	close(backup);
	set_signals_interactive();
	return (aborted);
}
