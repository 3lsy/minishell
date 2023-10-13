/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 16:10:02 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_children(pid_t *child_pids)
{
	int	i;

	i = 0;
	while (child_pids[i])
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

// rm  waitpid(pid, (int *)&sh->cl.exit_status, 0);
// waitpid for closing main process (to avoid zombie processes)
void	parent_exec(t_sh *sh, int id, pid_t pid)
{
	sh->cl.child_pids[id] = pid;
	g_sigint = pid;
	if (id == (sh->cl.n_cmds - 1))
	{
		waitpid(pid, (int *)&sh->cl.exit_status, 0);
		kill_children(sh->cl.child_pids);
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
	pid_t	pid;

	if (is_builtin(cmd->bin) >= 0)
	{
		if (redirect_io(sh, id, cmd) == FALSE || cmd->status > 0)
			return ;
		ft_execute_builtin(sh, cmd);
		reset_io(sh);
	}
	else if (is_builtin(cmd->bin) < 0)
	{
		pid = fork();
		if (pid == -1)
			exit_error(strerror(errno));
		else if (pid == 0
			&& redirect_io(sh, id, cmd) == TRUE
			&& cmd->status == 0)
			ft_execute(sh, cmd);
		else if (pid != 0)
			parent_exec(sh, id, pid);
		else
			exit(sh->cl.exit_status);
	}
}

// TODO:
// - Create pipes
// - Create processes and execute commands
// - Close pipes
// - Wait for processes to finish
// TODO:
// exit_error checked
void	ft_evaluator(t_sh *sh)
{
	int		i;
	t_ast	*cmd;

	sh->cl.pipes = create_pipes(sh->cl.n_cmds - 1);
	if (!sh->cl.pipes)
		exit_error(strerror(errno));
	sh->cl.child_pids = ft_calloc(sizeof(pid_t), sh->cl.n_cmds);
	if (!sh->cl.child_pids)
		exit_error(strerror(errno));
	eval_set_context(sh);
	signal(SIGINT, SIG_IGN);
	i = 0;
	cmd = sh->cl.ast;
	while (cmd)
	{
		execute_cmd(sh, i, cmd);
		cmd = cmd->next;
		i++;
	}
	evaluator_destructor(sh);
}
