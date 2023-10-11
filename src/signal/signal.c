/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/10 18:01:43 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint = NONE;

void	ft_sigint(__attribute__((unused)) int sig)
{
	(void)sig;
	ft_printf("^C");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_sigint = CTRLC;
}

void	ft_sigchild(int sig)
{
	kill(g_sigint, sig);
	if (sig == SIGINT)
		ft_printf("\n");
	else if (sig == SIGQUIT)
		ft_printf("Quit (core dumped)\n");
}

void	ft_empty(__attribute__((unused)) int sig)
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
	g_sigint = NONE;
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_empty);
	signal(SIGTSTP, ft_empty);
}
