/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:11:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/15 17:13:37 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

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

	sh->cl.exit_status = bt[is_builtin(cmd->bin)](
			cmd->ac, cmd->av, sh->plain_ev, sh
			);
}

void	ft_execute(t_sh *sh, t_ast *cmd)
{
	char	*cmd_path;

	if (!cmd->bin)
		return ;
	if (ft_strchr(cmd->bin, '/'))
	{
		if (is_dir(cmd->bin))
		{
			ft_fprintf(STDERR_FILENO, "minishell: %s: Is a directory\n",
				cmd->bin);
			exit(EXIT_FAILURE * 126);
		}
		execve(cmd->bin, cmd->av, sh->plain_ev);
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n",
			cmd->bin, strerror(errno));
		exit(EXIT_FAILURE * 126);
	}
	cmd_path = ft_which(cmd->bin, sh->ev, NULL);
	if (cmd_path)
		execve(cmd_path, cmd->av, sh->plain_ev);
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s: command not found\n",
			cmd->bin);
	free(cmd_path);
	exit(EXIT_FAILURE * 127);
}
