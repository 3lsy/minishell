/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/14 17:59:04 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
** cmd->status is to see if the command will be executed
** the return value of the function is to see if 
** it will continue to the next command or not
*/
int	redirect_input(t_sh *sh, int id, t_ast *cmd)
{
	int	i;
	int	status;

	if (id > 0)
		dup2(sh->cl.pipes[id - 1][0], STDIN_FILENO);
	i = 0;
	while (cmd->redir[i].id != NONE)
	{
		if (cmd->redir[i].id == SGL_L)
			cmd->status += input_redirection(sh, cmd->redir[i].file,
					is_builtin(cmd->bin) >= 0);
		else if (cmd->redir[i].id == DBL_L)
		{
			status = heredoc(sh, cmd->redir[i].file,
					is_builtin(cmd->bin) >= 0);
			if (status == CTRLC)
			{
				terminate_last_process(sh);
				return (FALSE);
			}
			cmd->status += status;
		}
		i++;
	}
	return (TRUE);
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
			cmd->status += output_redirection(cmd->redir[i].file);
		else if (cmd->redir[i].id == DBL_R)
			cmd->status += append_output(cmd->redir[i].file);
		i++;
	}
}

/*
** No builtin command reads from STDIN, so we don't need to redirect it.
*/

int	redirect_io(t_sh *sh, int id, t_ast *cmd)
{
	int	status;

	sh->cl.saved_stdout = dup(STDOUT_FILENO);
	status = redirect_input(sh, id, cmd);
	if (status == FALSE || cmd->bin == NULL)
		return (FALSE);
	redirect_output(sh, id, cmd);
	return (TRUE);
}

void	reset_io(t_sh *sh)
{
	dup2(sh->cl.saved_stdout, STDOUT_FILENO);
	close(sh->cl.saved_stdout);
}