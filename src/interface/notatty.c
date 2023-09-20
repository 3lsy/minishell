/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notatty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:14:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/21 01:27:20 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	notatty(t_sh *sh)
{
	char	*line;

	line = ft_get_next_line(STDIN_FILENO);
	while (line)
	{
		sh->cui.line = line;
		sh->cui.line_size = ft_strlen(line);
		ft_prompt(sh->cui.prompt);
		ft_printf("%s\n", line);
		if (sh->cui.line && (!sh->history
				|| ft_strcmp(sh->cui.line, sh->history->line)))
			save_line_history(sh, sh->cui.line);
		ft_analyzer(sh);
		free(line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	sh->cui.line = NULL;
	ft_exit(sh);
}
