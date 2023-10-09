/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:11:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 20:37:52 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Launch the corresponding builtin command.
*/
void	ft_execute_builtin(t_sh *sh, t_ast *cmd)
{
	const t_builtin	bt[7] = {
		ft_echo, ft_cd, ft_pwd,
		ft_export, ft_unset, ft_env,
		ft_exit
	};
	char			**ev;

	ev = convert_hashmap_to_ev(sh);
	sh->cl.exit_status = bt[is_builtin(cmd->bin)](cmd->ac, cmd->av, sh->ev, sh);
	free_ev(ev);
}

void	ft_execute(t_sh *sh, t_ast *cmd)
{
	char	*cmd_path;
	char	**ev;

	cmd_path = ft_which(cmd->bin, sh->ev, NULL);
	if (cmd_path)
	{
		ev = convert_hashmap_to_ev(sh);
		sh->cl.exit_status = execve(cmd_path, cmd->av, ev);
		free_ev(ev);
	}
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			cmd->bin);
	free(cmd_path);
	sh->cl.exit_status = 127;
	perror("minishell");
	exit(sh->cl.exit_status);
}
