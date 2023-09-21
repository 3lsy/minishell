/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:55:56 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/21 16:10:11 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** k24 is a hash function to store the environment variables
** in a hash table or hash map of size 16777213.
*/

static int	k24_insert(char **ev, char *str)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		key_index;

	tmp = ft_strchr(str, '=');
	key = ft_substr(str, 0, tmp - str);
	value = ft_strdup(tmp + 1);
	key_index = k24(key);
	ev[key_index] = value;
	free(key);
	return (key_index);
}

void	init_env(t_sh *sh, char **ev)
{
	int	i;

	sh->ev = ft_calloc(K24_SIZE, sizeof(char *));
	if (!sh->ev)
		exit_error(strerror(errno), sh);
	ft_memset(sh->keys, -1, K24_SIZE);
	i = 0;
	while (*ev)
	{
		sh->keys[i++] = k24_insert(sh->ev, *ev);
		ev++;
	}
}
