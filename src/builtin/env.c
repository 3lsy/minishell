/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:09:26 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 17:07:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av, char **ev,
			__attribute__((unused)) t_sh *sh)
{
	while (*ev)
		ft_printf("%s\n", (*ev)++);
	return (EXIT_SUCCESS);
}
