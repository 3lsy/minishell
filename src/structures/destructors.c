/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:49:31 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 20:04:21 by echavez-         ###   ########.fr       */
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

void	free_env(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->keys[i])
	{
		free(sh->ev[k24(sh->keys[i])]);
		sh->ev[k24(sh->keys[i])] = NULL;
		free(sh->keys[i]);
		sh->keys[i] = NULL;
		i++;
	}
	free(sh->ev);
}

void	free_ev(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		free(ev[i]);
		i++;
	}
	free(ev);
}

void	ft_destructor(t_sh *sh)
{
	evaluator_destructor(sh);
	analyzer_destructor(sh);
	unset_term(sh);
	save_history(sh);
	if (sh->ev)
		free_env(sh);
	if (sh->history)
		free_history(&sh->history);
	if (sh->cui.line)
		free(sh->cui.line);
	if (sh->cui.tmp_line)
		free(sh->cui.tmp_line);
	if (!sh->cui.interactive)
		ft_get_next_line(-503);
}

static __attribute__((destructor)) void	main_destructor(void)
{
	ft_sh(DESTRUCTOR);
}
