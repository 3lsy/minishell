/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 20:14:14 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_debug(void);

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
		redirect_io(sh, id, cmd);
		ft_execute_builtin(sh, cmd);
		reset_io(sh);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			exit_error(strerror(errno), sh);
		else if (pid == 0)
		{
			//redirect_io(sh, id, cmd);
			ft_execute(sh, cmd);
		}
		else
			sh->cl.child_pids[id] = pid;
	}
}

void	evaluator_destructor(t_sh *sh)
{
	int		i;
	t_ast	*cmd;

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
			waitpid(sh->cl.child_pids[i], (int *)&sh->cl.exit_status, 0);
		cmd = cmd->next;
		i++;
	}
	free(sh->cl.child_pids);
}

// TODO:
// - Create pipes
// - Create processes and execute commands
// - Close pipes
// - Wait for processes to finish
void	ft_evaluator(t_sh *sh)
{
	int		i;
	t_ast	*cmd;

	sh->cl.pipes = create_pipes(sh->cl.n_cmds - 1);
	if (!sh->cl.pipes)
		exit_error(strerror(errno), sh);
	sh->cl.child_pids = ft_calloc(sizeof(pid_t), sh->cl.n_cmds);
	if (!sh->cl.child_pids)
		exit_error(strerror(errno), sh);
	i = 0;
	cmd = sh->cl.ast;
	while (cmd)
	{
		execute_cmd(sh, i, cmd);
		cmd = cmd->next;
		i++;
	}
	evaluator_destructor(sh);
	// ft_debug();
}
