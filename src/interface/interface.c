/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:10:23 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/21 01:05:17 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_set(char *event)
{
	ft_printf("%s", tgetstr(event, NULL));
}

void	init_termcap(t_sh *sh)
{
	char	*termtype;
	int		connect;

	termtype = getenv("TERM");
	if (termtype == NULL)
		exit_error("Specify a terminal type with 'setenv TERM <term>'.", sh);
	connect = tgetent(NULL, termtype);
	if (connect < 0)
		exit_error("Could not access the termcap data base.", sh);
	if (connect == 0)
		exit_error("Terminal type is not defined.", sh);
}

// TODO
// Handle the case where stdin is not a terminal (e.g., when used in a pipeline)
void	init_termios(t_sh *sh)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &sh->cui.term) == -1)
			exit_error("Could not get the current termios attributes.", sh);
		sh->cui.term.c_lflag &= ~(ICANON | ECHO);
		sh->cui.term.c_cc[VMIN] = 1;
		sh->cui.term.c_cc[VTIME] = 0;
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term) == -1)
			exit_error("Could not set the termios attributes.", sh);
	}
	//else
		// exit_error("Standard input is not a terminal.", sh);
}

void	unset_term(t_sh *sh)
{
	if (!isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &sh->cui.term) == -1)
			return ;
		sh->cui.term.c_lflag |= (ICANON | ECHO);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term) == -1)
			ft_fprintf(2, "minishell: Could not set the termios attributes.\n");
	}
}

void	reset_cmdline(t_cui *cui)
{
	free(cui->line);
	free(cui->tmp_line);
	cui->tmp_line = NULL;
	cui->line = NULL;
	cui->cursor = 0;
	cui->line_size = 0;
	cui->history_cursor = NULL;
	cui->tmp_line = NULL;
}
