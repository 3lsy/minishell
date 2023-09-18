/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/18 17:16:53 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	ft_printf("^C\n");
}

static void	ft_empty(__attribute__((unused)) int sig)
{
}

/*
** Signals
** 1. CTRL + C
** 2. CTRL + \
** 3. CTRL + Z
*/

void	ft_signals(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_empty);
	signal(SIGTSTP, ft_empty);
}
