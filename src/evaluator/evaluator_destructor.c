/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_destructor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:18:05 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 17:42:58 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	evaluator_destructor(t_sh *sh)
{
	int		i;
	t_ast	*cmd;

	eval_unset_context(sh);
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
