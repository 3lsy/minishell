/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/12 14:02:17 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigint = NONE;

/*
** g_sigint is used as a boolean to know if the signal was received.
** The context of this handler is the interface.
*/
void	ft_sigint(__attribute__((unused)) int sig)
{
	(void)sig;
	ft_printf("^C");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_sigint = CTRLC;
}

/*
** g_sigint is used to store the PID of the process that received the signal.
** The context of this handler is the execution of a command. So if the PID
** is not 0, we kill the process that received the signal.
** States of g_sigint:
** 0: signal received from parent process.
** > 0: signal received from child process. (The value is its PID)
** -1 : signal received from parent process, to kill heredoc redirection.
** < -1: signal received from child process, to kill heredoc redirection.
**/
void	ft_sigchild(int sig)
{
	if (g_sigint > 0)
		kill(g_sigint, sig);
	else if (g_sigint < 0)
	{
		kill(-g_sigint, sig);
		g_sigint *= -1;
	}
	if (sig == SIGINT)
	{
		g_sigint *= -1;
		if (g_sigint == 0)
			g_sigint = -1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
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
