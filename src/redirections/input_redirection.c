/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:29:03 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/10 14:41:18 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Input redirection: <
** Takes the content of a file and redirects it to the command's STDIN.
** If the file doesn't exist, exit status is 1.
*/

void	input_redirection(t_sh *sh, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		sh->cl.exit_status = 1;
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}
