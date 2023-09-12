/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/12 21:51:25 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_minishell(t_sh *sh)
{
	while (TRUE)
	{
		ft_evaluator(sh);
		break ;
	}
}

int	main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av,
		__attribute__((unused)) char **ev)
{
	if (ac == 1)
	{
		ft_signals();
		ft_minishell(ft_sh());
		return (0);
	}
	return (1);
}

void	exit_error(char *e, t_sh *sh)
{
	ft_destructor(sh);
	ft_fprintf(STDERR_FILENO, "minishell: %s\n", e);
	exit(EXIT_FAILURE);
}

void	ft_destructor(t_sh *sh)
{
	if (sh->ast)
		free(sh->ast);
	if (sh->ev)
		free(sh->ev);
	if (sh->line)
		free(sh->line);
}
