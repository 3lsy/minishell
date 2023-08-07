/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:34:50 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/07 16:05:47 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint(int sig)
{
	(void)sig;
	ft_putendl("sigint");
}

void	ft_sigquit(int sig)
{
	(void)sig;
	ft_putendl("sigquit");
}

void	ft_sigtstp(int sig)
{
	(void)sig;
	ft_putendl("sigstp");
}
