/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:51:33 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 17:14:29 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*catch_cmd(char *cmd_path, char *tmpath, char **vpath)
{
	if (vpath)
		ft_free_split(&vpath);
	if (tmpath)
		free(tmpath);
	return (cmd_path);
}

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

	if (is_builtin(cmd) >= 0 || !ev[k24("PATH")])
		return (NULL);
	vpath = ft_split(ev[k24("PATH")], ':');
	i = 0;
	while (vpath && vpath[i])
	{
		tmpath = ft_strjoin(vpath[i++], "/", 0);
		if (!tmpath)
			return (catch_cmd(NULL, NULL, vpath));
		cmd_path = ft_strjoin(tmpath, cmd, 0);
		if (!cmd_path)
			return (catch_cmd(NULL, tmpath, vpath));
		free(tmpath);
		if (access(cmd_path, F_OK) == 0)
			return (catch_cmd(cmd_path, NULL, vpath));
		free(cmd_path);
	}
	ft_free_split(&vpath);
	return (NULL);
}

int	is_builtin(char *cmd)
{
	int			i;
	const char	*builtins[] = {
		"echo", "cd", "pwd",
		"export", "unset", "env",
		"exit", NULL
	};

	i = 0;
	while (cmd && builtins[i])
	{
		if (ft_strcmp((char *)builtins[i], cmd) == 0)
			return (i);
		i++;
	}
	return (-1);
}
