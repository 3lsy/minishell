/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/15 13:59:07 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_analyzer(t_sh *sh)
{
	sh->cl.tokens = ft_lexer(sh);
	if (!sh->cl.tokens)
	{
		sh->cl.exit_status = 2;
		return (EXIT_FAILURE);
	}
	if (ft_parser(sh->cl.tokens) == FALSE)
	{
		sh->cl.exit_status = 2;
		return (EXIT_FAILURE);
	}
	sh->cl.cmds = ft_split_cmds(sh->cl.tokens);
	if (!sh->cl.cmds)
	{
		sh->cl.exit_status = 2;
		return (EXIT_FAILURE);
	}
	ft_syntax_tree(sh);
	return (EXIT_SUCCESS);
}
