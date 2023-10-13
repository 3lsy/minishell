/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 18:57:38 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *option)
{
	int	i;

	if (option[0] != '-')
		return  (FALSE);
	i = 1;
	while (option[i])
	{
		if (option[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_echo(int ac, char **av, __attribute__((unused)) char **ev,
		__attribute__((unused)) t_sh *sh)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (ac > i && is_option(av[i]) == TRUE)
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
