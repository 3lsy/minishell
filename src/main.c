/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/15 13:57:34 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_minishell(t_sh *sh)
{
	while (TRUE)
	{
		if (g_sigint == CTRLC)
			sh->cl.exit_status = 130;
		reset_cmdline(&sh->cui);
		update_prompt(&sh->cui.prompt, sh->ev);
		ft_prompt(&sh->cui);
		ft_readline(&sh->cui, sh);
		if (!sh->cui.line || g_sigint == CTRLC)
			continue ;
		if (!sh->history || ft_strcmp(sh->cui.line, sh->history->line))
			save_line_history(sh, sh->cui.line);
		if (ft_analyzer(sh) != EXIT_FAILURE)
			ft_evaluator(sh);
		analyzer_destructor(sh);
		evaluator_destructor(sh);
	}
	ft_destructor(sh);
}

int	main(int ac, __attribute__((unused)) char **av, char **ev)
{
	t_sh	*sh;

	if (ac == 1)
	{
		sh = ft_sh(INIT);
		init_env(sh, ev);
		init_history(sh, sh->ev);
		init_prompt(&sh->cui.prompt, sh->ev);
		if (!isatty(STDIN_FILENO))
			notatty(sh);
		init_termcap(sh);
		init_termios(sh);
		ft_signals(CUI);
		ft_minishell(sh);
		return (0);
	}
	return (1);
}
