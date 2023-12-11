/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:10:23 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 18:38:57 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_set(char *event, char term_buffer[2048])
{
	ft_printf("%s", tgetstr(event, &term_buffer));
}

void	init_termcap(t_sh *sh)
{
	char	*termtype;
	int		connect;

	termtype = getenv("TERM");
	if (termtype == NULL)
		exit_error("Specify a terminal type with 'setenv TERM <term>'.");
	connect = tgetent(sh->cui.term_buffer, termtype);
	if (connect < 0)
		exit_error("Could not access the termcap data base.");
	if (connect == 0)
		exit_error("Terminal type is not defined.");
}

void	init_termios(t_sh *sh)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &sh->cui.term) == -1)
			exit_error("Could not get the current termios attributes.");
		if (tcgetattr(STDIN_FILENO, &sh->cui.term_backup) == -1)
			exit_error("Could not get the current termios attributes.");
		sh->cui.term.c_lflag &= ~(ICANON | ECHO);
		sh->cui.term.c_cc[VMIN] = 1;
		sh->cui.term.c_cc[VTIME] = 0;
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term) == -1)
			exit_error("Could not set the termios attributes.");
	}
}

void	unset_term(t_sh *sh)
{
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &sh->cui.term) == -1)
			return ;
		sh->cui.term.c_lflag |= (ICANON | ECHO);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term) == -1)
			ft_fprintf(STDERR_FILENO, ERR_TERMIOS);
		tgetent(NULL, "");
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
	g_sigint = NONE;
}
