/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/07 16:15:11 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_minishell(t_cmd *cmd)
{
	while (TRUE)
	{
		ft_evaluator(cmd);
		break ;
	}
}

t_cmd	*ft_cmd(void)
{
	static t_cmd	x = {
		.exit_status = 0,
		.line = NULL,
		.ast = NULL,
	};

	return (&x);
}

int	main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av,
		__attribute__((unused)) char **ev)
{
	t_cmd	*cmd;

	if (ac == 1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, ft_sigquit);
		signal(SIGTSTP, ft_sigtstp);
		cmd = ft_cmd();
		ft_minishell(cmd);
		return (0);
	}
	return (1);
}

void	exit_error(char *e)
{
	ft_perror("Error\n", EXIT_FAILURE);
	ft_perror(e, EXIT_FAILURE);
	exit(ft_perror("\n", EXIT_FAILURE));
}

static __attribute__((destructor)) void	sh_destructor(void)
{
	t_cmd	*cmd;

	cmd = ft_cmd();
	if (cmd->ast)
		free(cmd->ast);
}
