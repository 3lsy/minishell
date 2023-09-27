/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:29:42 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/27 11:20:51 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (is_redirection(tokens[i]))
			count++;
		i++;
	}
	return (count);
}

int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

/*
** Creates redirections and arguments arrays for a command
*/
void	extract_cmd_arrays(char **tokens, t_ast *cmd, int r, int a)
{
	int		i;

	cmd->redir = ft_calloc(sizeof(t_redir), count_redir(tokens) + 1);
	if (!cmd->redir)
		return ;
	cmd->ac = count_tokens(tokens) - count_redir(tokens) * 2;
	cmd->av = ft_calloc(sizeof(char *), cmd->ac + 1);
	if (!cmd->av)
		return (free(cmd->redir));
	i = 0;
	while (tokens[i])
	{
		if (is_redirection(tokens[i]))
		{
			cmd->redir[r++] = new_redir(tokens[i], tokens[i + 1]);
			i++;
		}
		else
			cmd->av[a++] = tokens[i];
		i++;
	}
}

void	ft_syntax_tree(t_sh *sh)
{
	int		i;
	t_ast	*tmp;

	i = 0;
	while (sh->cmds[i])
	{
		tmp = new_cmd();
		if (!tmp)
			exit_error(strerror(errno), sh);
		extract_cmd_arrays(sh->cmds[i], tmp, 0, 0);
		tmp->bin = tmp->av[0];
		tmp->next = sh->ast;
		sh->ast = tmp;
		i++;
	}
}
