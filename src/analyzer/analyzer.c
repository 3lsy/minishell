/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/27 19:55:05 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_analyzer(t_sh *sh)
{
	sh->tokens = ft_lexer(sh);
	if (!sh->tokens)
		return (EXIT_FAILURE);
	if (ft_parser(sh->tokens) == FALSE)
		return (EXIT_FAILURE);
	sh->cmds = ft_split_cmds(sh->tokens);
	if (!sh->cmds)
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

	if (sh->tokens)
		ft_free_split(&sh->tokens);
	if (sh->cmds)
	{
		i = 0;
		while (sh->cmds[i])
		{
			free(sh->cmds[i]);
			i++;
		}
		free(sh->cmds);
		sh->cmds = NULL;
	}
	if (sh->ast)
		free_ast(&sh->ast);
}
