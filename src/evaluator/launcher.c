/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:08:52 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/14 17:19:26 by echavez-         ###   ########.fr       */
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

// waitpid for closing main process (to avoid zombie processes)
void	parent_exec(t_sh *sh, int id, pid_t pid)
{
	sh->cl.child_pids[id] = pid;
	g_sigint = pid;
	if (id == (sh->cl.n_cmds - 1))
	{
		waitpid(pid, &sh->cl.exit_status, 0);
		sh->cl.exit_status = WEXITSTATUS(sh->cl.exit_status);
		kill_children(sh->cl.child_pids, sh->cl.n_cmds);
	}
	if (id > 0)
		close(sh->cl.pipes[id - 1][0]);
	if (id < (sh->cl.n_cmds - 1))
		close(sh->cl.pipes[id][1]);
}

void	launch_child(t_sh *sh, int i, t_ast *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error(strerror(errno));
	else if (pid == 0)
		execute_cmd(sh, i, cmd);
	else
		parent_exec(sh, i, pid);
}

void	launcher(t_sh *sh)
{
	int		i;
	t_ast	*cmd;

	i = 0;
	cmd = sh->cl.ast;
	while (cmd)
	{
		if (i == 0 && !cmd->next && is_builtin(cmd->bin) >= 0)
			execute_cmd(sh, i, cmd);
		else
			launch_child(sh, i, cmd);
		cmd = cmd->next;
		i++;
	}
}
