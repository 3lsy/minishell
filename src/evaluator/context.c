/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:11:08 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/13 19:57:16 by echavez-         ###   ########.fr       */
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
