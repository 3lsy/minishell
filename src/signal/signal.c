/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/13 19:57:39 by echavez-         ###   ########.fr       */
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
void	ft_sigcmd(int sig)
{
	if (sig == SIGINT)
		ft_printf("^C\n");
	else if (sig == SIGQUIT)
		ft_printf("Quit (core dumped)\n");
	if (g_sigint != 0)
		kill(g_sigint, sig);
}

void	ft_sighd(int sig)
{
	if (sig == SIGINT && g_sigint != CTRLC)
	{
		ft_printf("\n");
		exit(CTRLC);
	}
	else if (sig == SIGQUIT)
		ft_printf("Quit (core dumped)\n");
}

/*
** Signals
** 1. CTRL + C
** 2. CTRL + \
** 3. CTRL + Z
*/

void	ft_signals(int setting)
{
	if (setting == CUI)
	{
		g_sigint = NONE;
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (setting == EXEC)
	{
		signal(SIGINT, ft_sigcmd);
		signal(SIGQUIT, ft_sigcmd);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (setting == HEREDOC)
	{
		signal(SIGINT, ft_sighd);
		signal(SIGQUIT, ft_sighd);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (setting == UNSET)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
}
