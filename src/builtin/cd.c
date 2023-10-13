/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:39:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 19:50:36 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO:
//exit_error checked
int	change_dir(char *dir, t_sh *sh)
{
	if (!dir)
		return (EXIT_FAILURE);
	if (chdir(dir))
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", dir,
			strerror(errno));
		return (EXIT_FAILURE);
	}
	free(sh->ev[k24("OLDPWD")]);
	sh->ev[k24("OLDPWD")] = ft_strdup(sh->ev[k24("PWD")]);
	if (!sh->ev[k24("OLDPWD")])
		exit_error(strerror(errno));
	insert_key(ft_strdup("OLDPWD"), sh);
	free(sh->ev[k24("PWD")]);
	sh->ev[k24("PWD")] = getcwd(NULL, 0);
	if (!sh->ev[k24("PWD")])
		exit_error(strerror(errno));
	insert_key(ft_strdup("PWD"), sh);
	return (EXIT_SUCCESS);
}

int	ft_cd(int ac, char **av, __attribute__((unused)) char **ev, t_sh *sh)
{
	if (ac > 2)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (ac == 1)
	{
		if (!sh->ev[k24("HOME")])
		{
			ft_fprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		return (change_dir(sh->ev[k24("HOME")], sh));
	}
	else if (!ft_strcmp(av[1], "-"))
	{
		if (!sh->ev[k24("OLDPWD")])
		{
			ft_fprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
			return (EXIT_FAILURE);
		}
		return (change_dir(sh->ev[k24("OLDPWD")], sh));
	}
	else
		return (change_dir(av[1], sh));
}
