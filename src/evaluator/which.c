/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:51:33 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 17:19:08 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** which - shows the full path of (shell) commands
** @cmd: command to search
** @path: path to search in
*/

char	*ft_which(char *cmd, char **ev, char *cmd_path)
{
	char	**vpath;
	char	*tmpath;
	int		i;

	if (is_builtin(cmd) || !ev[k24("PATH")])
		return (NULL);
	vpath = ft_split(ev[k24("PATH")], ':');
	i = 0;
	while (vpath && vpath[i])
	{
		tmpath = ft_strjoin(vpath[i++], "/", 0);
		if (!tmpath)
			return (NULL);
		cmd_path = ft_strjoin(tmpath, cmd, 0);
		if (!cmd_path)
			return (NULL);
		ft_freejoin(&tmpath);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		ft_freejoin(&cmd_path);
	}
	return (NULL);
}

t_bool	is_builtin(char *cmd)
{
	int			i;
	const char	*builtins[] = {
		"echo", "cd", "pwd",
		"export", "unset", "env",
		"exit", "cd", NULL
	};

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp((char *)builtins[i], cmd) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
