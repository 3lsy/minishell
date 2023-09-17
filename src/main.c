/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 01:42:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/17 18:30:22 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** if (ft_analyzer(sh) == EXIT_FAILURE)
**   exit_error(strerror(errno), sh);
** if (ft_parser(sh) == EXIT_FAILURE)
**   exit_error(strerror(errno), sh);
*/
static void	ft_minishell(t_sh *sh)
{
	while (TRUE)
	{
		reset_cmdline(&sh->cui);
		ft_prompt(sh->cui.prompt);
		ft_readline(&sh->cui, sh);
		if (sh->cui.line && (!sh->history
				|| ft_strcmp(sh->cui.line, sh->history->line)))
			save_line_history(sh, sh->cui.line);
		ft_printf("{%s}\n", sh->cui.line);
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
