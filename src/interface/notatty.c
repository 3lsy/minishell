/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notatty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smile <smile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:14:32 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/13 18:16:35 by smile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	notatty(t_sh *sh)
{
	sh->cui.interactive = 0;
	sh->cui.line = ft_get_next_line(STDIN_FILENO);
	while (sh->cui.line)
	{
		sh->cui.line_size = ft_strlen(sh->cui.line);
		update_prompt(&sh->cui.prompt, sh->ev);
		ft_prompt(&sh->cui);
		ft_printf("%s\n", sh->cui.line);
		if (sh->cui.line && (!sh->history
				|| ft_strcmp(sh->cui.line, sh->history->line)))
			save_line_history(sh, sh->cui.line);
		if (ft_analyzer(sh) != EXIT_FAILURE)
			ft_evaluator(sh);
		analyzer_destructor(sh);
		evaluator_destructor(sh);
		free(sh->cui.line);
		sh->cui.line = ft_get_next_line(STDIN_FILENO);
	}
	free(sh->cui.line);
	sh->cui.line = NULL;
	exit(sh->cl.exit_status);
}
