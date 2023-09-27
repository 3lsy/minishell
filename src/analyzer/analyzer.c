/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:04:10 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/27 01:20:01 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_debug(void);

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

static void	analyzer_destructor(t_sh *sh)
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

void	ft_analyzer(t_sh *sh)
{
	sh->tokens = ft_lexer(sh);
	if (!sh->tokens)
		return ;
	if (ft_parser(sh->tokens) == FALSE)
		return (ft_free_split(&sh->tokens));
	sh->cmds = ft_split_cmds(sh->tokens);
	if (!sh->cmds)
		return (ft_free_split(&sh->tokens));
	ft_syntax_tree(sh);
	ft_debug();
	analyzer_destructor(sh);
}
