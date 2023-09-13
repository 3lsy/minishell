/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:55:56 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/13 18:37:29 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** k24 is a hash function to store the environment variables
** in a hash table or hash map of size 16777213.
*/

void	k24_insert(char **ev, char *str)
{
	char	*key;
	char	*value;
	char	*tmp;

	tmp = ft_strchr(str, '=');
	key = ft_substr(str, 0, tmp - str);
	value = ft_strdup(tmp + 1);
	ev[k24(key)] = value;
	free(key);
	free(value);
}

void	init_env(t_sh *sh, char **ev)
{
	sh->ev = ft_calloc(16777213, sizeof(char *));
	if (!sh->ev)
		exit_error(strerror(errno), sh);
	while (*ev)
	{
		k24_insert(sh->ev, *ev);
		ev++;
	}
}
