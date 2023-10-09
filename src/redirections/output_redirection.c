/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:30:52 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/08 19:36:42 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Output redirection: >
** Takes the content of a command's STDOUT and redirects it to a file.
** If the file doesn't exist, it is created.
*/

void	output_redirection(t_sh *sh, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit_error(strerror(errno), sh);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
