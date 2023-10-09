/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:22:19 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/09 17:02:37 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** hashmap ev -> [ NULL, NULL, NULL, "value", NULL, NULL, "value", ...]
** keys -> ["key", "key", -1, -1, -1, ...]
** transform to:
** ev = ["key=value", "key=value", "key=value", ...]
*/
int	ft_pwd(__attribute__((unused)) int ac,
			__attribute__((unused)) char **av,
			__attribute__((unused)) char **ev,
			__attribute__((unused)) t_sh *sh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("minishell: pwd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
