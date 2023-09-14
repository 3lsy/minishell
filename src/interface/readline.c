/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:48:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/14 22:05:26 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print is for debug when e == 4 (ctrl + d)
** Replace exit() with our builtin exit (status?)
*/
void	key_event(char *e, t_cui *cui, t_sh *sh)
{
	if (ft_strcmp(e, CTRL_D) == 0)
	{
		ft_printf("exit\n");
		exit(503);
	}
	else if (ft_strcmp(e, DEL) == 0)
		delete_key(cui, sh);
	else if (ft_strcmp(e, LEFT_ARROW) == 0)
		left_key(cui);
	else if (ft_strcmp(e, RIGHT_ARROW) == 0)
		right_key(cui);
	else if (ft_strcmp(e, UP_ARROW) == 0)
		ft_printf("up");
	else if (ft_strcmp(e, DOWN_ARROW) == 0)
		ft_printf("down");
}

void	write_input(char c, t_cui *cui, t_sh *sh)
{
	ft_printf("%c", c);
	ft_strinsert(&cui->line, c, cui->cursor);
	if (!cui->line)
		exit_error("Could not allocate memory.", sh);
	term_set(CLEAR_RIGHT);
	term_set(STORE_CURSOR);
	ft_printf("%s", cui->line + cui->cursor + 1);
	term_set(RESTORE_CURSOR);
	cui->cursor++;
	cui->line_size++;
}

/*
** len = # of chars/bytes read
*/
void	ft_readline(t_cui *cui, t_sh *sh)
{
	char	buf[MAX_CODE_SIZE + 1];
	int		len;

	ft_bzero(buf, MAX_CODE_SIZE + 1);
	while (!ft_strchr(buf, '\n'))
	{
		len = read(STDIN_FILENO, buf, MAX_CODE_SIZE);
		if (len == -1)
			exit_error(strerror(errno), sh);
		buf[len] = 0;
		if (len > 1 || !ft_isprint(buf[0]))
			key_event(buf, cui, sh);
		else
			write_input(buf[0], cui, sh);
	}
	ft_printf("\n");
}
