/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:01:29 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/17 18:13:21 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	left_key(t_cui *cui)
{
	if (cui->cursor > 0)
		cui->cursor--;
	else
		return (0);
	term_set(LEFT_CURSOR);
	return (1);
}

int	right_key(t_cui *cui)
{
	if (cui->cursor < cui->line_size)
		cui->cursor++;
	else
		return (0);
	term_set(RIGHT_CURSOR);
	return (1);
}

int	delete_key(t_cui *cui, t_sh *sh)
{
	char	*tmp;

	if (!left_key(cui))
		return (0);
	term_set(DELETE_CHAR);
	cui->line[cui->cursor] = '\0';
	tmp = ft_strjoin(cui->line, cui->line + cui->cursor + 1, 0);
	if (!tmp)
		exit_error(strerror(errno), sh);
	free(cui->line);
	cui->line = tmp;
	cui->line_size--;
	return (1);
}

int	up_key(t_cui *cui, t_sh *sh)
{
	if (!cui->history_cursor && !cui->tmp_line)
	{
		cui->history_cursor = sh->history;
		if (cui->line_size > 0)
			cui->tmp_line = ft_strdup(cui->line);
	}
	else if (!sh->history || !cui->history_cursor->next)
		return (0);
	else
		cui->history_cursor = cui->history_cursor->next;
	if (!cui->history_cursor)
		return (0);
	change_line(cui, sh, cui->history_cursor->line);
	return (1);
}

int	down_key(t_cui *cui, t_sh *sh)
{
	if (!cui->history_cursor || !sh->history)
		return (0);
	if (cui->history_cursor->prev)
	{
		cui->history_cursor = cui->history_cursor->prev;
		change_line(cui, sh, cui->history_cursor->line);
	}
	else
	{
		cui->history_cursor = NULL;
		change_line(cui, sh, cui->tmp_line);
		free(cui->tmp_line);
		cui->tmp_line = NULL;
	}
	return (1);
}
