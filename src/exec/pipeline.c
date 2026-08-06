/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:28:45 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 10:47:20 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pipe_setup(t_cmd *cmd, int prev_fd, int *pipefd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static pid_t	fork_stage(t_shell *sh, t_cmd *cmd, int prev_fd, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		set_signals_child();
		child_pipe_setup(cmd, prev_fd, pipefd);
		exit(exec_child(sh, cmd));
	}
	return (pid);
}

static void	close_parent_fds(int *prev_fd, t_cmd *cmd, int *pipefd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
		*prev_fd = -1;
}

static int	wait_all(pid_t last)
{
	int		wstatus;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = wait(&wstatus);
	while (pid > 0)
	{
		if (pid == last)
			last_status = wstatus;
		pid = wait(&wstatus);
	}
	set_signals_interactive();
	return (report_status(last_status));
}

int	run_pipeline(t_shell *sh)
{
	t_cmd	*cmd;
	int		prev_fd;
	int		pipefd[2];
	pid_t	last;

	prev_fd = -1;
	last = -1;
	cmd = sh->cmds;
	set_signals_exec();
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			break ;
		last = fork_stage(sh, cmd, prev_fd, pipefd);
		close_parent_fds(&prev_fd, cmd, pipefd);
		cmd = cmd->next;
	}
	return (wait_all(last));
}
