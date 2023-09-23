/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:08:59 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/23 18:22:37 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_key(char *key, t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->keys[i])
	{
		if (!ft_strcmp(sh->keys[i], key))
		{
			sh->ec--;
			free(sh->keys[i]);
			sh->keys[i++] = NULL;
			while (sh->keys[i])
			{
				sh->keys[i - 1] = sh->keys[i];
				i++;
			}
			break ;
		}
		i++;
	}
}

/*
** ev in this case is sh->ev, not the result of convert_hashmap_to_ev
*/

int	ft_unset(int ac, char **av, char **ev, t_sh *sh)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ev[k24(av[i])])
		{
			free(ev[k24(av[i])]);
			ev[k24(av[i])] = NULL;
		}
		unset_key(av[i], sh);
		i++;
	}
	return (EXIT_SUCCESS);
}
