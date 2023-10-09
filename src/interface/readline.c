/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:48:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 17:23:38 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints the character and inserts it in the line at the cursor position
*/
void	write_input(char c, t_cui *cui, t_sh *sh)
{
	ft_printf("%c", c);
	ft_strinsert(&cui->line, c, cui->cursor);
	if (!cui->line)
		exit_error("Could not allocate memory.", sh);
	term_set(CLEAR_RIGHT, sh->cui.term_buffer);
	term_set(STORE_CURSOR, sh->cui.term_buffer);
	ft_printf("%s", cui->line + cui->cursor + 1);
	term_set(RESTORE_CURSOR, sh->cui.term_buffer);
	cui->cursor++;
	cui->line_size++;
}

void	paste_str(char *str, t_cui *cui, t_sh *sh)
{
	int	i;

	i = 0;
	while (str[i])
		write_input(str[i++], cui, sh);
}

/*
** Manges events triggered by the user
** (e.g. pressing the arrow keys, deleting a character, pasting, etc.)
*/
void	key_event(char *e, t_cui *cui, t_sh *sh)
{
	if (ft_strcmp(e, CTRL_D) == 0 && !cui->line_size)
	{
		ft_printf("\n");
		ft_exit(0, NULL, NULL. sh);
	}
	else if (ft_strcmp(e, DEL) == 0)
		delete_key(cui, sh);
	else if (ft_strcmp(e, LEFT_ARROW) == 0)
		left_key(cui, sh);
	else if (ft_strcmp(e, RIGHT_ARROW) == 0)
		right_key(cui, sh);
	else if (ft_strcmp(e, UP_ARROW) == 0)
		up_key(cui, sh);
	else if (ft_strcmp(e, DOWN_ARROW) == 0)
		down_key(cui, sh);
	else if (ft_isprintable(e))
		paste_str(e, cui, sh);
}

/*
** len = # of chars/bytes read per read()
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

void	change_line(t_cui *cui, t_sh *sh, char *line)
{
	while (cui->cursor > 0)
		left_key(cui, sh);
	term_set(CLEAR_RIGHT, sh->cui.term_buffer);
	free(cui->line);
	cui->line = NULL;
	cui->line_size = 0;
	if (line)
	{
		ft_printf("%s", line);
		cui->line = ft_strdup(line);
		if (!cui->line)
			exit_error(strerror(errno), sh);
		cui->line_size = ft_strlen(line);
	}
	cui->cursor = cui->line_size;
}
