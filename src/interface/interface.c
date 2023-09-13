/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:10:23 by echavez-          #+#    #+#             */
/*   Updated: 2023/09/13 15:47:53 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_termcap(t_sh *sh)
{
	char	*termtype;
	int		connect;

	termtype = getenv("TERM");
	if (termtype == NULL)
		exit_error("Specify a terminal type with 'setenv TERM <term>'.", sh);
	connect = tgetent(NULL, termtype);
	if (connect < 0)
		exit_error("Could not access the termcap data base.", sh);
	if (connect == 0)
		exit_error("Terminal type is not defined.", sh);
}
