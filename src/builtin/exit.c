/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:07:24 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/15 15:54:35 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_islong(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (ft_strlen(str + i) > 19)
		return (FALSE);
	if (ft_strlen(str + i) == 19)
	{
		if (ft_strcmp(str + i, "9223372036854775807") > 0)
			return (FALSE);
	}
	return (TRUE);
}

int	ft_exit(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av,
			__attribute__((unused)) char **ev,
			t_sh *sh)
{
	if (sh->cl.n_cmds < 2)
		ft_printf("exit\n");
	if (ac == 2)
	{
		if (!ft_isnum(av[1]) || ft_strlen(av[1]) > 20 || !ft_islong(av[1]))
		{
			ft_fprintf(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n", av[1]);
			sh->cl.exit_status = 2;
		}
		else
			sh->cl.exit_status = ft_atoi(av[1]);
		exit(sh->cl.exit_status);
	}
	else if (ac > 2)
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		sh->cl.exit_status = 1;
	}
	else
		exit(sh->cl.exit_status);
	return (sh->cl.exit_status);
}

void	exit_error(char *e)
{
	ft_fprintf(STDERR_FILENO, "minishell: %s\n", e);
	exit(EXIT_FAILURE);
}
