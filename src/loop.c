/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 16:56:54 by isoulima          #+#    #+#             */
/*   Updated: 2026/09/04 11:58:12 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	assign_status(t_shell *sh, int status)
{
	sh->status = status;
	return (-1);
}

static int	parse_line(t_shell *sh, char *line, t_token **tokens)
{
	int	err;

	err = 0;
	*tokens = lexer(line, &err);
	if (err || syntax_check(*tokens))
		return (assign_status(sh, 2));
	sh->cmds = parser(*tokens, &err);
	if (err)
		return (assign_status(sh, 2));
	if (!sh->cmds)
		return (-1);
	if (expand_cmds(sh, sh->cmds))
		return (assign_status(sh, 1));
	if (collect_heredocs(sh, sh->cmds))
		return (assign_status(sh, 130));
	return (0);
}

static void	process_line(t_shell *sh, char *line)
{
	t_token	*tokens;

	tokens = NULL;
	if (parse_line(sh, line, &tokens) == 0)
		sh->status = execute(sh);
	token_free(tokens);
	cmd_free(sh->cmds);
	sh->cmds = NULL;
}

int	shell_loop(t_shell *sh)
{
	char	*line;

	set_signals_interactive();
	line = readline(PROMPT);
	while (line)
	{
		if (g_signal == SIGINT)
			sh->status = 130;
		g_signal = 0;
		if (*line)
			add_history(line);
		process_line(sh, line);
		free(line);
		set_signals_interactive();
		line = readline(PROMPT);
	}
	write(STDOUT_FILENO, "exit\n", 5);
	return (sh->status);
}
