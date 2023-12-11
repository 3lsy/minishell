/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 15:17:51 by echavez-          #+#    #+#             */
/*   Updated: 2023/12/11 16:43:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_plain_ev(t_sh *sh)
{
	if (sh->plain_ev)
		free_ev(sh->plain_ev);
	sh->plain_ev = convert_hashmap_to_ev(sh);
}

/*
** Names are case-sensitive.
** Consisting solely of letters, numbers, and underscores, 
** and beginning with a letter or underscore. Names are used as shell variable.
*/

int	valid_name(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

/*
** TODO:
** Check if when `export key=` or key="" it creates a value of ""
** Check if when `export key` without equal sign it creates a key 
** with value of NULL
*/
static int	ft_setenv(char *arg, t_sh *sh)
{
	char	*key;
	char	*tmp;

	tmp = ft_strchr(arg, '=');
	if (!tmp)
	{
		insert_key(ft_strdup(arg), sh);
		update_plain_ev(sh);
		return (1);
	}
	key = k24_insert(sh->ev, arg);
	if (!key)
		return (0);
	insert_key(key, sh);
	update_plain_ev(sh);
	return (1);
}

void	print_declarations(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->keys[i])
	{
		ft_printf("declare -x %s", sh->keys[i]);
		if (sh->ev[k24(sh->keys[i])])
			ft_printf("=\"%s\"", sh->ev[k24(sh->keys[i])]);
		ft_printf("\n");
		i++;
	}
}

//TODO:
//exit_error checked
int	ft_export(int ac, char **av, __attribute__((unused)) char **ev, t_sh *sh)
{
	int	i;
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ac > 1)
	{
		i = 1;
		while (av[i])
		{
			if (!valid_name(av[i]))
			{
				ft_printf("minishell: export: `%s': not a valid identifier\n",
					av[i]);
				exit_status = EXIT_FAILURE;
			}
			else if (!ft_setenv(av[i], sh))
				exit_error(strerror(errno));
			i++;
		}
	}
	else
		print_declarations(sh);
	return (exit_status);
}
