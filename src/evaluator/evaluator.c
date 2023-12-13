/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smile <smile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/13 17:14:43 by smile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_children(pid_t *child_pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
		kill(child_pids[i++], SIGTERM);
}

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

// waitpid for closing main process (to avoid zombie processes)
void	parent_exec(t_sh *sh, int id, pid_t pid)
{
	sh->cl.child_pids[id] = pid;
	g_sigint = pid;
	if (id == (sh->cl.n_cmds - 1))
	{
		waitpid(pid, &sh->cl.exit_status, 0);
		kill_children(sh->cl.child_pids, sh->cl.n_cmds);
	}
	if (id > 0)
		close(sh->cl.pipes[id - 1][0]);
	if (id < (sh->cl.n_cmds - 1))
		close(sh->cl.pipes[id][1]);
	sh->cl.exit_status = WEXITSTATUS(sh->cl.exit_status);
}

/*
** If the command is a builtin, no fork is needed.
** If the command is not a builtin, fork and execute.
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
		if (redirect_io(sh, id, cmd) == TRUE || cmd->status == 0)
			ft_execute_builtin(sh, cmd);
	}
	else if (is_builtin(cmd->bin) < 0)
	{
		if (redirect_io(sh, id, cmd) == TRUE
			&& cmd->status == 0)
			ft_execute(sh, cmd);
	}
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
	int		i;
	t_ast	*cmd;
	pid_t	pid;

	sh->cl.pipes = create_pipes(sh->cl.n_cmds - 1);
	if (!sh->cl.pipes)
		exit_error(strerror(errno));
	sh->cl.child_pids = ft_calloc(sizeof(pid_t), sh->cl.n_cmds);
	if (!sh->cl.child_pids)
		exit_error(strerror(errno));
	eval_set_context(sh);
	i = 0;
	cmd = sh->cl.ast;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			exit_error(strerror(errno));
		else if (pid == 0)
			execute_cmd(sh, i, cmd);
		else
			parent_exec(sh, i, pid);
		cmd = cmd->next;
		i++;
	}
}
