/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/23 19:40:07 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** if (ft_analyzer(sh) != EXIT_FAILURE)
**    ft_parser(sh);
*/
static void	ft_minishell(t_sh *sh)
{
	while (TRUE)
	{
		reset_cmdline(&sh->cui);
		ft_prompt(&sh->cui);
		ft_readline(&sh->cui, sh);
		if (!sh->cui.line || g_sigint)
			continue ;
		if (!sh->history || ft_strcmp(sh->cui.line, sh->history->line))
			save_line_history(sh, sh->cui.line);
		ft_analyzer(sh);
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
		init_history(sh, sh->ev);
		init_prompt(&sh->cui.prompt, sh->ev);
		if (!isatty(STDIN_FILENO))
			notatty(sh);
		init_termcap(sh);
		init_termios(sh);
		ft_signals();
		ft_minishell(sh);
		return (0);
	}
	return (1);
}
