/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:01:29 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/14 22:06:03 by echavez-         ###   ########.fr       */
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
