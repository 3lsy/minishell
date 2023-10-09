/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 19:27:26 by echavez-         ###   ########.fr       */
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

/*
** No builtin command reads from STDIN, so we don't need to redirect it.
*/

void	redirect_io(t_sh *sh, int id, t_ast *cmd)
{
	if (is_builtin(cmd->bin) >= 0)
		redirect_input(sh, id, cmd);
	else
		sh->cl.saved_stdout = dup(STDOUT_FILENO);
	redirect_output(sh, id, cmd);
}

void	reset_io(t_sh *sh)
{
	dup2(sh->cl.saved_stdout, STDOUT_FILENO);
	close(sh->cl.saved_stdout);
}
