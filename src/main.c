/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/11 18:00:58 by echavez-         ###   ########.fr       */
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

t_sh	*ft_sh(void)
{
	static t_sh	x = {
		.exit_status = 0,
		.line = NULL,
		.ast = NULL,
		.ev = NULL,
		.cui = {
			.prompt = {
				.username = NULL,
				.hostname = NULL,
				.pwd = NULL,
				.symbol = '$',
			},
		},
	};

	return (&x);
}

int	main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av,
		__attribute__((unused)) char **ev)
{
	if (ac == 1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigquit);
		signal(SIGTSTP, ft_sigtstp);
		ft_minishell(ft_sh());
		return (0);
	}
	return (1);
}

void	exit_error(char *e, t_sh *sh)
{
	ft_destructor(sh);
	ft_perror("Error\n", EXIT_FAILURE);
	ft_perror(e, EXIT_FAILURE);
	exit(ft_perror("\n", EXIT_FAILURE));
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

static __attribute__((destructor)) void	sh_destructor(void)
{
	t_sh	*cmd;

	cmd = ft_sh();
	if (cmd->ast)
		free(cmd->ast);
}
