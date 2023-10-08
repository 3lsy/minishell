/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:51:33 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/08 17:55:05 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** which - shows the full path of (shell) commands
** @cmd: command to search
** @path: path to search in
*/

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
		if (ft_strcmp(builtins[i], cmd) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
