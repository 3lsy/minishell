/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:11:08 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 16:08:06 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eval_set_context(t_sh *sh)
{
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term_backup) == -1)
		exit_error("Could not set the termios attributes.");
	ft_signals(EXEC);
}

void	eval_unset_context(t_sh *sh)
{
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term) == -1)
		exit_error("Could not set the termios attributes.");
	ft_signals(CUI);
}

void	evaluator_destructor(t_sh *sh)
{
	int		i;
	t_ast	*cmd;

	eval_unset_context(sh);
	i = 0;
	while (i < sh->cl.n_cmds - 1)
	{
		close(sh->cl.pipes[i][0]);
		close(sh->cl.pipes[i][1]);
		i++;
	}
	if (sh->cl.pipes)
		free(sh->cl.pipes);
	sh->cl.pipes = NULL;
	cmd = sh->cl.ast;
	i = 0;
	while (cmd)
	{
		if (is_builtin(cmd->bin) < 0)
			waitpid(sh->cl.child_pids[i], &sh->cl.exit_status, 0);
		cmd = cmd->next;
		i++;
	}
	free(sh->cl.child_pids);
	sh->cl.child_pids = NULL;
}
