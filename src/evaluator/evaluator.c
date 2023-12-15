/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/15 17:13:43 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	(*create_pipes(int n))[2]
{
	int	(*pipes)[2];
	int	id;

	pipes = ft_calloc(sizeof(int [2]), n);
	if (!pipes)
		return (NULL);
	id = 0;
	while (id < n)
	{
		if (pipe(pipes[id]) == -1)
		{
			free(pipes);
			return (NULL);
		}
		id++;
	}
	return (pipes);
}

/*
** To define where the input and output will be redirected,
** we have to redirect first define where the input and output
** will be redirected, in this order of priority:
** - Pipe input
** - Pipe output
** - Input redirection
** - Output redirection
** Reset input and output redirection for builtin commands.
*/
void	execute_cmd(t_sh *sh, int id, t_ast *cmd)
{
	cmd->status = 0;
	if (is_builtin(cmd->bin) >= 0)
	{
		if (redirect_io(sh, id, cmd) == TRUE && cmd->status == 0)
			ft_execute_builtin(sh, cmd);
		reset_io(sh);
	}
	else if (is_builtin(cmd->bin) < 0)
	{
		if (redirect_io(sh, id, cmd) == TRUE
			&& cmd->status == 0)
			ft_execute(sh, cmd);
	}
	if (sh->cl.n_cmds > 1 || is_builtin(cmd->bin) < 0)
		exit(sh->cl.exit_status);
}

/*
** Create pipes and child_pids arrays.
** Execute commands.
** Wait for all child processes to finish.
** Free pipes and child_pids arrays.
** // signal(SIGINT, SIG_IGN);
*/

void	ft_evaluator(t_sh *sh)
{
	sh->cl.pipes = create_pipes(sh->cl.n_cmds - 1);
	if (!sh->cl.pipes)
		exit_error(strerror(errno));
	sh->cl.child_pids = ft_calloc(sizeof(pid_t), sh->cl.n_cmds);
	if (!sh->cl.child_pids)
		exit_error(strerror(errno));
	eval_set_context(sh);
	launcher(sh);
}
