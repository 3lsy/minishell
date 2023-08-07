/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:49:59 by echavez-          #+#    #+#             */
/*   Updated: 2023/08/07 15:53:34 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_cmd(char *bin, int ac, char **av)
{
	t_ast	*new;

	new = ft_calloc(sizeof(t_ast), 1);
	if (!new)
		return (NULL);
	new->id = 0;
	new->bin = bin;
	new->ac = ac;
	new->av = av;
	new->left = NULL;
	new->right = NULL;
	new->file = NULL;
	return (new);
}
