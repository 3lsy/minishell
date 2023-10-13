/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notatty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:14:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 20:03:32 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	notatty(t_sh *sh)
{
	char	*line;

	sh->cui.interactive = 0;
	line = ft_get_next_line(STDIN_FILENO);
	while (line)
	{
		sh->cui.line = line;
		sh->cui.line_size = ft_strlen(line);
		update_prompt(&sh->cui.prompt, sh->ev);
		ft_prompt(&sh->cui);
		ft_printf("%s\n", line);
		if (sh->cui.line && (!sh->history
				|| ft_strcmp(sh->cui.line, sh->history->line)))
			save_line_history(sh, sh->cui.line);
		if (ft_analyzer(sh) != EXIT_FAILURE)
			ft_evaluator(sh);
		analyzer_destructor(sh);
		evaluator_destructor(sh);
		free(line);
		line = ft_get_next_line(STDIN_FILENO);
	}
	free(line);
	sh->cui.line = NULL;
	exit(sh->cl.exit_status);
}
