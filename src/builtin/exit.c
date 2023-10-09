/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:07:24 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 17:15:33 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av,
			__attribute__((unused)) char **ev,
			t_sh *sh)
{
	t_byte	status;

	status = sh->cl.exit_status;
	ft_destructor(sh);
	ft_printf("exit\n");
	exit(status);
}

void	exit_error(char *e, t_sh *sh)
{
	ft_destructor(sh);
	ft_fprintf(STDERR_FILENO, "minishell: %s\n", e);
	exit(EXIT_FAILURE);
}
