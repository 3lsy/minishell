/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:16:25 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/08 20:26:59 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_key(char *key, t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->keys[i])
	{
		if (!ft_strcmp(sh->keys[i], key))
			return ;
		i++;
	}
	sh->keys[i] = key;
	sh->ec++;
}

/*
** k24 is a hash function to store the environment variables
** in a hash table or hash map of size 16777213.
*/

char	*k24_insert(char **ev, char *str)
{
	char	*key;
	char	*value;
	char	*tmp;

	tmp = ft_strchr(str, '=');
	key = ft_substr(str, 0, tmp - str);
	if (!key)
		return (NULL);
	value = ft_strdup(tmp + 1);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	ev[k24(key)] = value;
	return (key);
}

void	init_env(t_sh *sh, char **ev)
{
	int	i;

	sh->ev = ft_calloc(K24_SIZE, sizeof(char *));
	if (!sh->ev)
		exit_error(strerror(errno), sh);
	ft_memset(sh->keys, 0, K24_SIZE);
	i = 0;
	while (*ev)
	{
		sh->keys[i++] = k24_insert(sh->ev, *ev);
		if (!sh->keys[i - 1])
			exit_error(strerror(errno), sh);
		ev++;
	}
	sh->ec = i;
}

char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(key, "=", 0);
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, value, 0);
	free(tmp);
	return (str);
}

/*
** Every key with an empty value is ignored.
** They are the keys that were exported wihtout any value.
*/
char	**convert_hashmap_to_ev(t_sh *sh)
{
	char	**ev;
	int		i;

	ev = ft_calloc(sizeof(char **), sh->ec + 1);
	if (!ev)
		return (NULL);
	ev[sh->ec] = NULL;
	i = 0;
	while (i < sh->ec)
	{
		if (!sh->ev[k24(sh->keys[i])])
			continue ;
		ev[i] = join_key_value(sh->keys[i], sh->ev[k24(sh->keys[i])]);
		if (!ev[i])
		{
			free_ev(ev);
			return (NULL);
		}
		i++;
	}
	return (ev);
}
