/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:09:26 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 19:23:50 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av, char **ev,
			__attribute__((unused)) t_sh *sh)
{
	int	i;

	i = 0;
	while (i < sh->ec)
	{
		if (ev[i])
			ft_printf("%s\n", ev[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
