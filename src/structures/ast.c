/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:49:59 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/27 01:09:32 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	new_redir(char *redir, char *file)
{
	t_redir	new;

	new.id = is_operator(redir, 0);
	new.file = file;
	return (new);
}

t_ast	*new_cmd(void)
{
	t_ast	*new;

	new = ft_calloc(sizeof(t_ast), 1);
	if (!new)
		return (NULL);
	new->bin = NULL;
	new->ac = 0;
	new->av = NULL;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}
