/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:42:28 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/13 16:02:52 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	ft_printf("\t[");
	while (tokens[i])
	{
		ft_printf("%s", tokens[i]);
		if (tokens[i + 1])
			ft_printf(", ");
		i++;
	}
	ft_printf("]\n");
}

void	print_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("\t[");
	while (cmds[i])
	{
		ft_printf("[");
		j = 0;
		while (cmds[i][j])
		{
			ft_printf("%s", cmds[i][j]);
			if (cmds[i][j + 1])
				ft_printf(", ");
			j++;
		}
		ft_printf("]");
		if (cmds[i + 1])
			ft_printf(", ");
		i++;
	}
	ft_printf("]\n");
}

void	print_ast_content(t_ast *ast)
{
	int	j;

	if (ast->bin)
		ft_printf("CMD: %s\n\t[", ast->bin);
	else
		ft_printf("CMD: \n\t[NULL");
	j = 0;
	while (j < ast->ac)
	{
		ft_printf("%s", ast->av[j]);
		if (ast->av[j + 1])
			ft_printf(", ");
		j++;
	}
	ft_printf("]\n");
	ft_printf("Redir: \n");
	j = 0;
	while (ast->redir[j].id)
	{
		ft_printf("\t%d %s\n", ast->redir[j].id, ast->redir[j].file);
		j++;
	}
}

void	print_ast(t_ast *ast)
{
	while (ast)
	{
		print_ast_content(ast);
		ast = ast->next;
	}
}

void	ft_debug(void)
{
	t_sh	*sh;

	sh = ft_sh(INIT);
	ft_printf("sh->cl.tokens:\n");
	print_tokens(sh->cl.tokens);
	ft_printf("sh->cl.cmds:\n");
	print_cmds(sh->cl.cmds);
	ft_printf("sh->cl.ast:\n");
	print_ast(sh->cl.ast);
}
