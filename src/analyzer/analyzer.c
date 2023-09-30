/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/30 20:53:04 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_analyzer(t_sh *sh)
{
	sh->cl.tokens = ft_lexer(sh);
	if (!sh->cl.tokens)
		return (EXIT_FAILURE);
	if (ft_parser(sh->cl.tokens) == FALSE)
		return (EXIT_FAILURE);
	sh->cl.cmds = ft_split_cmds(sh->cl.tokens);
	if (!sh->cl.cmds)
		return (EXIT_FAILURE);
	ft_syntax_tree(sh);
	return (EXIT_SUCCESS);
}

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
