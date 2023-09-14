/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:48:35 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/14 17:36:32 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print is for debug when e == 4 (ctrl + d)
** Replace exit() with our builtin exit (status?)
*/
void	key_event(char *e, int len)
{
	if (len == 1 && e[0] == 4)
	{
		ft_printf("exit\n");
		exit(503);
	}
}

/*
** len = # of chars/bytes read
*/
int	ft_readline(__attribute__((unused)) t_cui *cui)
{
	char	buf[MAX_CODE_SIZE + 1];
	int		len;

	ft_bzero(buf, MAX_CODE_SIZE + 1);
	while (!ft_strchr(buf, '\n'))
	{
		len = read(STDIN_FILENO, buf, MAX_CODE_SIZE);
		if (len == -1)
			return (EXIT_FAILURE);
		buf[len] = 0;
		if (len > 1 || !ft_isprint(buf[0]))
			key_event(buf, len);
		else
			ft_printf("%c", buf[0]);
	}
	return (EXIT_SUCCESS);
}
