/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:32:40 by nbechon           #+#    #+#             */
/*   Updated: 2023/07/12 15:07:27 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commande_pwd(char **word)
{
        char	cwd[1000];
        int	i;

	i = 0;
	if (word[1] != NULL && word[1][0] == '-')
	{
		printf ("pwd: ");
		while ((word[1][i] == '-' && i < 2) || i != 2)
		{
			printf ("%c", word[1][i]);
			i++;
		}
		printf (": invalid option\n");
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	else
		return (perror("PWD"), EXIT_FAILURE);
}
