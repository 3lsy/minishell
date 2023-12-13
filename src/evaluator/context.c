/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smile <smile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:11:08 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/13 17:23:19 by smile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eval_set_context(t_sh *sh)
{
	if (sh->cui.interactive)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term);
	ft_signals(EXEC);
}

void	eval_unset_context(t_sh *sh)
{
	if (sh->cui.interactive)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &sh->cui.term);
	ft_signals(CUI);
}
