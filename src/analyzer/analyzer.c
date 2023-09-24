/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/24 17:49:54 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_analyzer(t_sh *sh)
{
	int		i;

	sh->tokens = ft_lexer(sh);
	if (!sh->tokens)
		return ;
	i = 0;
	ft_printf("[");
	while (sh->tokens[i])
		ft_printf("%s, ", sh->tokens[i++]);
	ft_printf("]\n");
	if (ft_parser(sh->tokens) == FALSE)
	{
		ft_free_split(&sh->tokens);
		return ;
	}
	ft_free_split(&sh->tokens);
}
