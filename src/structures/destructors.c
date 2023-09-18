/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:49:31 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/17 20:33:53 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_history **history)
{
	t_history	*tmp;

	if (!*history)
		return ;
	while (*history)
	{
		tmp = *history;
		*history = tmp->next;
		free(tmp->line);
		tmp->line = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	ft_destructor(t_sh *sh)
{
	unset_term(sh);
	save_history(sh);
	if (sh->history)
		free_history(&sh->history);
	if (sh->ast)
		free(sh->ast);
	if (sh->ev)
		free(sh->ev);
	if (sh->cui.line)
		free(sh->cui.line);
}
