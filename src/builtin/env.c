/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:09:26 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/23 15:17:20 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av, char **ev)
{
	while (*ev)
		ft_printf("%s\n", (*ev)++);
	return (EXIT_SUCCESS);
}
