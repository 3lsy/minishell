/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 21:11:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/06 20:03:08 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute(t_sh *sh)
{
	(void)sh;
	return (0);
}

void	ft_redirect(int i, t_sh *sh, int n)
{
	if (i > 0)
		redirect_input();
	if (i < (n - 1))
		redirect_output();
}

void	redirect_input(void)
{
	dup2(pipes[i - 1][0], STDIN_FILENO);
	close(pipes[i - 1][1]);
}

void	redirect_output(void)
{
	dup2(pipes[i][1], STDOUT_FILENO);
	close(pipes[i][0]);
}
