/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/08 20:05:55 by echavez-         ###   ########.fr       */
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
int	execute_cmd(t_sh *sh, int id, t_ast *cmd)
{
	pid_t	pid;

	if (is_builtin(cmd->bin))
	{
		redirect_io(sh, id, cmd);
		ft_execute_builtin(sh, id, cmd);
		reset_io(sh, id, cmd);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			exit_error(strerror(errno), sh);
		else if (pid == 0)
		{
			redirect_io(sh, id, cmd);
			ft_execute(sh, id, cmd);
		}
		else
			sh->cl.pids[id] = pid;
	}
}

// TODO:
// - Create pipes
// - Create processes and execute commands
// - Close pipes
// - Wait for processes to finish
// TMP:
// - free pipes not in a destructor

void	ft_evaluator(t_sh *sh)
{
	int	i;

	sh->cl.pipes = create_pipes(sh->cl.n_cmds - 1);
	if (!sh->cl.pipes)
		exit_error(strerror(errno), sh);
	i = 0;
	while (i < sh->cl.n_cmds)
	{
		execute_cmd(sh, i, sh->cl.cmds[i]);
		i++;
	}
	free(sh->cl.pipes);
	ft_debug();
}
