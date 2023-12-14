/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:11:58 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/14 15:04:41 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ctrl_left(t_cui *cui, t_sh *sh)
{
	int	i;

	i = 0;
	while (cui->cursor > 0 && cui->line[cui->cursor - 1] == ' ')
	{
		left_key(cui, sh);
		i++;
	}
	while (cui->cursor > 0 && cui->line[cui->cursor - 1] != ' ')
	{
		left_key(cui, sh);
		i++;
	}
	return (i);
}

int	ctrl_right(t_cui *cui, t_sh *sh)
{
	int	i;

	i = 0;
	while (cui->cursor < cui->line_size && cui->line[cui->cursor] == ' ')
	{
		right_key(cui, sh);
		i++;
	}
	while (cui->cursor < cui->line_size && cui->line[cui->cursor] != ' ')
	{
		right_key(cui, sh);
		i++;
	}
	return (i);
}

int	home_key(t_cui *cui, t_sh *sh)
{
	int	i;

	i = 0;
	while (cui->cursor > 0)
	{
		left_key(cui, sh);
		i++;
	}
	return (i);
}

int	end_key(t_cui *cui, t_sh *sh)
{
	int	i;

	i = 0;
	while (cui->cursor < cui->line_size)
	{
		right_key(cui, sh);
		i++;
	}
	return (i);
}

int	ctrl_l(t_cui *cui, t_sh *sh)
{
	int	i;

	term_set(CLEAR_SCREEN, sh->cui.term_buffer);
	ft_prompt(cui);
	ft_printf("%s", cui->line);
	i = 0;
	while (cui->line_size - i > cui->cursor)
	{
		term_set(LEFT_CURSOR, sh->cui.term_buffer);
		i++;
	}
	return (i);
}
