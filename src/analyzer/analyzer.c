/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/21 00:43:04 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// DEBUG LINES
// ft_printf("{%s}\n", sh->cui.line);
void	ft_analyzer(t_sh *sh)
{
	ft_printf("{%s}\n", sh->cui.line);
	char	**test = ft_split_args(sh->cui.line);
	if (!test)
		return ;
	for (int i = 0; test[i]; i++)
		ft_printf("[%s]\n", test[i]);
}
