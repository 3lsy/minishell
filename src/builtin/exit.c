/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:07:24 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/21 00:16:26 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_sh *sh)
{
	t_byte	status;

	status = sh->exit_status;
	ft_destructor(sh);
	ft_printf("\nexit\n");
	exit(status);
}

void	exit_error(char *e, t_sh *sh)
{
	ft_destructor(sh);
	ft_fprintf(STDERR_FILENO, "minishell: %s\n", e);
	exit(EXIT_FAILURE);
}
