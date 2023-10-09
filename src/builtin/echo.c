/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 17:08:18 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(int ac, char **av, __attribute__((unused)) char **ev,
		__attribute__((unused)) t_sh *sh)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (ac > 1 && !ft_strcmp(av[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (i < ac)
	{
		ft_printf("%s", av[i]);
		if (i + 1 < ac)
			ft_printf(" ");
		i++;
	}
	if (!n_flag)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
