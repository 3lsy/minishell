/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/14 17:36:09 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** if (ft_analyzer(sh) == EXIT_FAILURE)
**   exit_error(strerror(errno), sh);
** ft_evaluator(sh);
*/
static void	ft_minishell(t_sh *sh)
{
	while (TRUE)
	{
		ft_prompt(sh->cui.prompt);
		if (ft_readline(&sh->cui) == EXIT_FAILURE)
			exit_error(strerror(errno), sh);
		break ;
	}
	ft_destructor(sh);
}

int	main(int ac, __attribute__((unused)) char **av, char **ev)
{
	t_sh	*sh;

	if (ac == 1)
	{
		sh = ft_sh();
		init_env(sh, ev);
		init_prompt(&sh->cui.prompt, sh->ev);
		init_termcap(sh);
		init_termios(sh);
		ft_signals();
		ft_minishell(sh);
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
	unset_term(sh);
	if (sh->ast)
		free(sh->ast);
	if (sh->ev)
		free(sh->ev);
	if (sh->cui.line)
		free(sh->cui.line);
}
