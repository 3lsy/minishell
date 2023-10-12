/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/12 20:19:20 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(t_sh *sh, int id, t_ast *cmd)
{
	int	i;

	if (id > 0)
		dup2(sh->cl.pipes[id - 1][0], STDIN_FILENO);
	i = 0;
	while (cmd->redir[i].id != NONE)
	{
		if (cmd->redir[i].id == SGL_L)
			input_redirection(sh, cmd->redir[i].file);
		else if (cmd->redir[i].id == DBL_L)
			heredoc(sh, cmd->redir[i].file);
		if (g_sigint == CTRLC)
			break ;
		i++;
	}
}

void	redirect_output(t_sh *sh, int id, t_ast *cmd)
{
	int	i;

	if (id < (sh->cl.n_cmds - 1))
		dup2(sh->cl.pipes[id][1], STDOUT_FILENO);
	i = 0;
	while (cmd->redir[i].id != NONE)
	{
		if (cmd->redir[i].id == SGL_R)
			output_redirection(sh, cmd->redir[i].file);
		else if (cmd->redir[i].id == DBL_R)
			append_output(sh, cmd->redir[i].file);
		i++;
	}
}

void	terminate_last_process(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->cl.child_pids[i] != 0)
	{
		if (sh->cl.child_pids[i + 1] == 0)
			kill(sh->cl.child_pids[i], SIGTERM);
		i++;
	}
}

/*
** No builtin command reads from STDIN, so we don't need to redirect it.
*/

int	redirect_io(t_sh *sh, int id, t_ast *cmd)
{
	int	sig_bkp;

	sh->cl.saved_stdout = dup(STDOUT_FILENO);
	sig_bkp = g_sigint;
	g_sigint = 0;
	ft_signals(HEREDOC);
	redirect_input(sh, id, cmd);
	if (g_sigint == CTRLC)
	{
		g_sigint = sig_bkp;
		ft_signals(EXEC);
		terminate_last_process(sh);
		return (FALSE);
	}
	g_sigint = sig_bkp;
	ft_signals(EXEC);
	redirect_output(sh, id, cmd);
	return (TRUE);
}

void	reset_io(t_sh *sh)
{
	dup2(sh->cl.saved_stdout, STDOUT_FILENO);
	close(sh->cl.saved_stdout);
}
