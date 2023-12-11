/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_destructor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:20:12 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 17:20:33 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_ast(t_ast **ast)
{
	t_ast	*tmp;

	while (*ast)
	{
		tmp = *ast;
		*ast = (*ast)->next;
		free(tmp->av);
		free(tmp->redir);
		free(tmp);
	}
	*ast = NULL;
}

void	analyzer_destructor(t_sh *sh)
{
	int	i;

	if (sh->cl.tokens)
		ft_free_split(&sh->cl.tokens);
	if (sh->cl.cmds)
	{
		i = 0;
		while (sh->cl.cmds[i])
		{
			free(sh->cl.cmds[i]);
			i++;
		}
		free(sh->cl.cmds);
		sh->cl.cmds = NULL;
	}
	if (sh->cl.ast)
		free_ast(&sh->cl.ast);
}
