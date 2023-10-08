/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:32:12 by echavez-          #+#    #+#             */
/*   Updated: 2023/10/08 19:37:22 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Output redirection: >>
** Takes the content of a command's STDOUT and appends it to a file.
** If the file doesn't exist, it is created.
*/

void	append_output(t_sh *sh, char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		exit_error(strerror(errno), sh);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
